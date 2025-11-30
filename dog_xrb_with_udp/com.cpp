#include "serialPort/SerialPort.h"
#include <unistd.h>
#include <iostream>
#include <fstream>
#include <chrono>

float spd[60] = {0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1, 1.1, 1.2, 1.3, 1.4, 1.5, 1.6, 1.7, 1.8, 1.9, 2, 2.1, 2.2, 2.3, 2.4, 2.5, 2.6, 2.7, 2.8, 2.9, 3, 3.1, 3.2, 3.3, 3.4, 3.5, 3.6, 3.7, 3.8, 3.9, 4, 4.1, 4.2, 4.3, 4.4, 4.5, 4.6, 4.7, 4.8, 4.9, 5.0, 5.1, 5.2, 5.3, 5.4, 5.5, 5.6, 5.7, 5.8, 5.9, 6.0};

int main()
{
    SerialPort serial("/dev/ttyUSB0");
    MotorCmd cmd;
    MotorData data;
    cmd.motorType = MotorType::GO_M8010_6;
    cmd.id = 12;
    cmd.mode = 1;
    cmd.K_P = 0;
    cmd.K_W = 0.16;
    cmd.Pos = 0;
    cmd.T = 0;

    unsigned int i = 0;

    std::ofstream outfile1("./log1.txt");
    std::ofstream outfile2("./log2.txt");
    std::ofstream outfile3("./log3.txt");
    if ((!outfile1.is_open()) || (!outfile2.is_open()) || (!outfile3.is_open()))
    {
        return 0;
    }

    auto maxDuration = std::chrono::milliseconds(500);
    auto start = std::chrono::high_resolution_clock::now();
    auto start1 = std::chrono::high_resolution_clock::now();
    auto end1 = std::chrono::high_resolution_clock::now();
    auto end2 = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end1 - start);
    auto duration_m = std::chrono::duration_cast<std::chrono::milliseconds>(end1 - end2);
    auto duration_m1 = std::chrono::duration_cast<std::chrono::milliseconds>(end1 - end2);
    start = std::chrono::high_resolution_clock::now();
    for (i = 0; i < 330; i++)
    {
        start1 = std::chrono::high_resolution_clock::now();
        while (true)
        {

            end1 = std::chrono::high_resolution_clock::now();
            duration = std::chrono::duration_cast<std::chrono::milliseconds>(end1 - start);
            duration_m1 = std::chrono::duration_cast<std::chrono::milliseconds>(end1 - start1);
            duration_m = std::chrono::duration_cast<std::chrono::milliseconds>(end1 - end2);
            cmd.W = -0.1 * i;
            serial.sendRecv(&cmd, &data);

            if (duration_m.count() > 50)
            {
                end2 = end1;
                outfile1 << duration.count() << " ";
                outfile2 << data.W << " ";
                outfile3 << data.T << " ";
            }

            if (duration_m1 > maxDuration)
            {
                break;
            }
        }
        std::cout << i << std::endl;
    }
    // for (i = 0; i < 330; i++)
    // {
    //     start1 = std::chrono::high_resolution_clock::now();
    //     while (true)
    //     {

    //         end1 = std::chrono::high_resolution_clock::now();
    //         duration = std::chrono::duration_cast<std::chrono::milliseconds>(end1 - start);
    //         duration_m1 = std::chrono::duration_cast<std::chrono::milliseconds>(end1 - start1);
    //         duration_m = std::chrono::duration_cast<std::chrono::milliseconds>(end1 - end2);
    //         cmd.W = 0.1 * i;
    //         serial.sendRecv(&cmd, &data);

    //         if (duration_m.count() > 50)
    //         {
    //             end2 = end1;
    //             outfile1 << duration.count() << " ";
    //             outfile2 << data.W << " ";
    //             outfile3 << data.T << " ";
    //         }

    //         if (duration_m1 > maxDuration)
    //         {
    //             break;
    //         }
    //     }
    //     std::cout << i << std::endl;
    // }

    outfile1.close();
    outfile2.close();
    outfile3.close();
}
