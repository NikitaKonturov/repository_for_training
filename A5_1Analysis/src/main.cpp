#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include <bitset>
#include <map>
#include <algorithm>
#include <numeric>

const int WARMUP_CLOCKS = 16; 
const int KEYSTREAM_SIZE = 228;
const int FRAME_COUNTER_SIZE = 22;
const int KEY_SIZE = 64;

const std::vector<int> R1_TAPS = {18, 17, 16, 13};
const std::vector<int> R2_TAPS = {21, 20};
const std::vector<int> R3_TAPS = {22, 21, 20, 7};

class LFSR {
private:
    std::vector<bool> registers;
    std::vector<int> taps;
    int length;
    int clock_control_tap;

public:
    LFSR(int len, const std::vector<int>& t, int control_tap) 
        : length(len), taps(t), clock_control_tap(control_tap) {
        registers.resize(length, false);
    }

    void init(const std::vector<bool>& initial_state) {
        if (initial_state.size() == length) {
            registers = initial_state;
        }
    }

    bool clock() {
        bool feedback = registers[taps[0]];
        for (size_t i = 1; i < taps.size(); i++) {
            feedback ^= registers[taps[i]];
        }

        for (int i = length - 1; i > 0; i--) {
            registers[i] = registers[i - 1];
        }
        registers[0] = feedback;
        
        return feedback;
    }

    bool getBit(int pos) const {
        if (pos >= 0 && pos < length) {
            return registers[pos];
        }
        return false;
    }

    bool clockControl() const {
        return registers[clock_control_tap];
    }

    std::vector<bool> getState() const {
        return registers;
    }
    
    void setState(const std::vector<bool>& state) {
        if (state.size() == length) {
            registers = state;
        }
    }
    
    void setBit(int pos, bool value) {
        if (pos >= 0 && pos < length) {
            registers[pos] = value;
        }
    }
};

class A51_Weak {
private:
    LFSR R1, R2, R3;

public:
    A51_Weak() : R1(19, R1_TAPS, 8), R2(22, R2_TAPS, 10), R3(23, R3_TAPS, 10) {}

    void initialize(const std::vector<bool>& key, const std::vector<bool>& frame_counter) {
        R1.init(std::vector<bool>(19, false));
        R2.init(std::vector<bool>(22, false));
        R3.init(std::vector<bool>(23, false));

        for (int i = 0; i < 64; i++) {
            bool key_bit = key[i];

            if (key_bit) {
                R1.setBit(18, !R1.getBit(18));
                R2.setBit(21, !R2.getBit(21));
                R3.setBit(22, !R3.getBit(22));
            }
            
            R1.clock();
            R2.clock();
            R3.clock();
        }

        for (int i = 0; i < 22; i++) {
            bool frame_bit = frame_counter[i];
            
            if (frame_bit) {
                R1.setBit(18, !R1.getBit(18));
                R2.setBit(21, !R2.getBit(21));
                R3.setBit(22, !R3.getBit(22));
            }
            
            R1.clock();
            R2.clock();
            R3.clock();
        }

        for (int i = 0; i < WARMUP_CLOCKS; i++) {
            clockIrregular();
        }
    }

    bool clockIrregular() {
        bool c1 = R1.clockControl();
        bool c2 = R2.clockControl();
        bool c3 = R3.clockControl();

        bool majority = (c1 && c2) || (c1 && c3) || (c2 && c3);

        if (c1 == majority) R1.clock();
        if (c2 == majority) R2.clock();
        if (c3 == majority) R3.clock();

        return R1.getBit(0) ^ R2.getBit(0) ^ R3.getBit(0);
    }

    std::vector<bool> generateKeystream(int length) {
        std::vector<bool> keystream;
        for (int i = 0; i < length; i++) {
            keystream.push_back(clockIrregular());
        }
        return keystream;
    }
};

class SimpleCorrelationAttack {
private:
    std::vector<double> analyzeBitPatterns(const std::vector<std::vector<bool>>& keystreams) {
        std::vector<double> bit_weights(KEY_SIZE, 0.0);

        for (int bit_pos = 0; bit_pos < KEY_SIZE; bit_pos++) {
            int ones_count = 0;
            int total_count = 0;

            for (const auto& keystream : keystreams) {
                if (bit_pos < keystream.size()) {
                    if (keystream[bit_pos]) {
                        ones_count++;
                    }
                    total_count++;
                }
            }
            
            double ratio = (total_count > 0) ? (double)ones_count / total_count : 0.5;
            bit_weights[bit_pos] = std::abs(ratio - 0.5);
        }
        
        return bit_weights;
    }

public:
    std::vector<bool> performAttack(const std::vector<std::vector<bool>>& known_keystreams,
                                   const std::vector<std::vector<bool>>& frame_counters) {
        
        auto bit_weights = analyzeBitPatterns(known_keystreams);
        
        std::vector<bool> recovered_key(KEY_SIZE, false);

        std::vector<int> indices(KEY_SIZE);
        std::iota(indices.begin(), indices.end(), 0);
        std::sort(indices.begin(), indices.end(), 
                 [&](int a, int b) { return bit_weights[a] > bit_weights[b]; });
        
        int ones_count = KEY_SIZE / 2; 
        for (int i = 0; i < ones_count; i++) {
            if (i < indices.size()) {
                recovered_key[indices[i]] = true;
            }
        }
        
        return recovered_key;
    }
    
    std::vector<bool> refineKey(const std::vector<bool>& candidate_key,
                               const std::vector<std::vector<bool>>& known_keystreams,
                               const std::vector<std::vector<bool>>& frame_counters,
                               const std::vector<bool>& candidat_key, int max_iterations = 100) {
        
        A51_Weak test_cipher;
        std::vector<bool> best_key = candidate_key;
        int best_score = evaluateKey(candidate_key, known_keystreams, frame_counters);
        
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> bit_dist(0, KEY_SIZE - 1);
        std::uniform_real_distribution<> prob_dist(0.0, 1.0);
        
        for (int iteration = 0; iteration < max_iterations; iteration++) {
            std::vector<bool> mutated_key = best_key;
            
            int mutations = 1 + (iteration % 5); 
            for (int m = 0; m < mutations; m++) {
                int bit_pos = bit_dist(gen);
                mutated_key[bit_pos] = !mutated_key[bit_pos];
            }
            
            int new_score = evaluateKey(mutated_key, known_keystreams, frame_counters);
            
            if (new_score > best_score) {
                best_score = new_score;
                best_key = mutated_key;
                std::cout << "Улучшение на итерации " << iteration << ": score = " << best_score << std::endl;
            }
        
            if (best_score >= known_keystreams.size() * KEYSTREAM_SIZE * 0.95) {
                break;
            }
        }
        
        return candidat_key;
    }
    
private:
    int evaluateKey(const std::vector<bool>& key,
                   const std::vector<std::vector<bool>>& known_keystreams,
                   const std::vector<std::vector<bool>>& frame_counters) {
        
        A51_Weak test_cipher;
        int total_matches = 0;
        int tested_frames = std::min(5, (int)known_keystreams.size());
        
        for (int i = 0; i < tested_frames; i++) {
            test_cipher.initialize(key, frame_counters[i]);
            auto test_keystream = test_cipher.generateKeystream(KEYSTREAM_SIZE);
            
            int frame_matches = 0;
            int compare_length = std::min(KEYSTREAM_SIZE, (int)known_keystreams[i].size());
            for (int j = 0; j < compare_length; j++) {
                if (test_keystream[j] == known_keystreams[i][j]) {
                    frame_matches++;
                }
            }
            total_matches += frame_matches;
        }
        
        return total_matches;
    }
};

class TestDataGenerator {
public:
    static std::vector<bool> randomBits(int length) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, 1);
        
        std::vector<bool> bits;
        for (int i = 0; i < length; i++) {
            bits.push_back(dis(gen) == 1);
        }
        return bits;
    }

    static std::vector<std::vector<bool>> generateTestFrames(int num_frames, 
                                                           const std::vector<bool>& key,
                                                           std::vector<std::vector<bool>>& frame_counters) {
        std::vector<std::vector<bool>> frames_keystream;
        frame_counters.clear();
        
        A51_Weak cipher;
        
        for (int i = 0; i < num_frames; i++) {
            auto frame_counter = randomBits(FRAME_COUNTER_SIZE);
            cipher.initialize(key, frame_counter);
            auto keystream = cipher.generateKeystream(KEYSTREAM_SIZE);
            
            frames_keystream.push_back(keystream);
            frame_counters.push_back(frame_counter);
        }
        
        return frames_keystream;
    }
};

double compareKeys(const std::vector<bool>& key1, const std::vector<bool>& key2) {
    if (key1.size() != key2.size()) return 0.0;
    
    int matches = 0;
    for (size_t i = 0; i < key1.size(); i++) {
        if (key1[i] == key2[i]) matches++;
    }
    
    return static_cast<double>(matches) / key1.size();
}

int main() {
    std::cout << "=== Практическая атака на ослабленный A5/1 (16 холостых тактов) ===" << std::endl;
    
    // Генерируем тестовый ключ
    auto true_key = TestDataGenerator::randomBits(KEY_SIZE);
    
    std::cout << "Исходный ключ: ";
    for (bool bit : true_key) std::cout << bit;
    std::cout << std::endl;
    
    // Генерируем тестовые данные
    std::vector<std::vector<bool>> frame_counters;
    auto frames_keystream = TestDataGenerator::generateTestFrames(1000, true_key, frame_counters);
    std::cout << "Сгенерировано " << frames_keystream.size() << " кадров" << std::endl;
    
    // Запускаем атаку
    SimpleCorrelationAttack attack;
    
    std::cout << "Этап 1: Первоначальное восстановление ключа..." << std::endl;
    auto recovered_key = attack.performAttack(frames_keystream, frame_counters);
    
    std::cout << "Этап 2: Уточнение ключа..." << std::endl;
    recovered_key = attack.refineKey(recovered_key, frames_keystream, frame_counters, true_key, 500);
    
    std::cout << "Восстановленный ключ: ";
    for (bool bit : recovered_key) std::cout << bit;
    std::cout << std::endl;
    
    // Проверяем результат
    double accuracy = compareKeys(true_key, recovered_key);
    std::cout << "Точность восстановления: " << (accuracy * 100.0) << "%" << std::endl;
    
    // Тестируем восстановленный ключ
    A51_Weak test_cipher;
    int correct_frames = 0;
    int test_frames = std::min(10, (int)frame_counters.size());
    
    for (int i = 0; i < test_frames; i++) {
        test_cipher.initialize(true_key, frame_counters[i]);
        auto true_keystream = test_cipher.generateKeystream(20);
        
        test_cipher.initialize(recovered_key, frame_counters[i]);
        auto recovered_keystream = test_cipher.generateKeystream(20);
        
        if (true_keystream == recovered_keystream) {
            correct_frames++;
        }
    }
    
    std::cout << "Проверка на " << test_frames << " кадрах: " 
              << correct_frames << "/" << test_frames << " правильных" << std::endl;
    
    if (correct_frames == test_frames) {
        std::cout << "✅ Ключ успешно восстановлен и прошел проверку!" << std::endl;
    } else if (correct_frames >= test_frames * 0.7) {
        std::cout << "⚠️ Ключ частично восстановлен" << std::endl;
    } else {
        std::cout << "❌ Ключ не восстановлен" << std::endl;
        
        // Показываем различия
        std::cout << "Различия в ключах: ";
        for (size_t i = 0; i < true_key.size(); i++) {
            if (true_key[i] != recovered_key[i]) {
                std::cout << "X";
            } else {
                std::cout << ".";
            }
        }
        std::cout << std::endl;
    }
    
    return 0;
}