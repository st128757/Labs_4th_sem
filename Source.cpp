#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>

int main() {
    std::vector<double> measurements; // массив для хранения измерений

    // Укажите здесь полный путь к вашему файлу
    std::string filename = "C:\\programming SPBU\\Labs\\1\\results.txt";
    
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Feilure " << filename << std::endl;
        std::cerr << "check path" << std::endl;
        return 1;
    }

    std::cout << "Success. File is opened" << filename << std::endl;

    double value;
    int count = 0;

    // Читаем пары "номер значение" из файла
    while (file >> value) {
        measurements.push_back(value);
        count++;
        std::cout << "Count " << count << ", value " << value << std::endl;
    }

    file.close();

    /*Выводим все значения
    std::cout << "\n=== Result ===" << std::endl;
    std::cout << "The number of values " << measurements.size() << std::endl;
    std::cout << "Values:" << std::endl;

    for (size_t i = 0; i < measurements.size(); i++) {
        std::cout << "measurements[" << i << "] = " << measurements[i];

        std::cout << std::endl;
    }
    */

    //считаем среднее арифм
    double a = 0;
    for (int i = 0; i < 50; ++i)
    {
        a += measurements[i];
    }
    double arithmetic_mean = a / (measurements.size());
    std::cout << "arithmetic mean: " << arithmetic_mean << std::endl;

    //считаем погрешность
    double delta = (0.05 * arithmetic_mean + 0.05) / 100;
    std::cout << "rate error: " << delta;

    // ========== НОВЫЙ КОД: СОХРАНЕНИЕ РЕЗУЛЬТАТОВ В ФАЙЛ ==========

// Укажите путь к файлу для сохранения результатов
    std::string output_filename = "C:\\programming SPBU\\Labs\\1\\deviations.txt";
    // Или можно использовать относительный путь:
    // std::string output_filename = "deviations.txt";

    std::ofstream output_file(output_filename);
    if (!output_file.is_open()) {
        std::cerr << "Failed to create output file: " << output_filename << std::endl;
        return 1;
    }

    std::cout << "\n=== Writing deviations to file ===" << std::endl;
    std::cout << "Output file: " << output_filename << std::endl;

    // Записываем заголовок
    output_file << "Deviations from arithmetic mean (" << arithmetic_mean << ")" << std::endl;
    output_file << "Index\tValue\tDeviation\tDeviation^2" << std::endl;  // добавлен новый столбец
    output_file << "------------------------------------------------" << std::endl;  // удлинил разделитель

    // Записываем отклонения для каждого измерения
    double hlp = 0; //для рассчета дисперсии
    for (size_t i = 0; i < measurements.size(); i++) {
        double deviation = measurements[i] - arithmetic_mean;
        double deviation_squared = pow(deviation, 2);
        hlp += deviation_squared;
        /*// Вывод в консоль (для проверки)
        std::cout << "measurements[" << i << "] = " << measurements[i]
            << " - deviation = " << deviation
            << " - deviation^2 = " << deviation_squared << std::endl;*/

        // Запись в файл
        output_file << i << "\t"
            << std::fixed << std::setprecision(6) << measurements[i] << "\t"
            << deviation << "\t"
            << deviation_squared << std::endl;
    }

    //считаем дисперсию
    double disp = sqrt((double)1/49 * hlp);
    double skp = disp / sqrt(50);

    // Записываем итоговую статистику
    output_file << "------------------------------------------------" << std::endl;
    output_file << "Arithmetic mean: " << arithmetic_mean << std::endl;
    output_file << "Total measurements: " << measurements.size() << std::endl;
    output_file << "Dispersia: " << disp << std::endl;
    std::cout << "Srednaya kvadratichnaya pogreshnost: " << skp << std::endl;

    output_file.close();
    std::cout << "Dispersia: " << disp << std::endl;
    std::cout << "Srednaya kvadratichnaya pogreshnost: " << skp << std::endl;
    std::cout << "\nData successfully written to " << output_filename << std::endl;

    // ========== КОНЕЦ НОВОГО КОДА ==========
    return 0;
}