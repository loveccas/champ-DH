#include "serialPort/SerialPort.h"
#include <unistd.h>
#include "run.h"
#include "udp/udp.h"
#include <iostream>
#include <fstream>

#define pi 3.1415
#define UDP_TARGET_PORT 5002
#define UDP_LISTEN_PORT 5002
#define UDP_TARGET_IP "192.168.31.234"

udp::UDPReceiver udp_receiver;
SerialPort serial("/dev/ttyUSB0");
MotorCmd cmd;
MotorData data;
char *endptr;
// 上电初始角度(绝对零位)
float initial[12] = {0};
// 相对绝对零位角度(目标角度)
float target[12] = {0};
bool get_initial_angle();
// 不能设置为1，防止越界
char id[5];
char pos[30];
char *id_ = id;
char *pos_ = pos;
int i, j, k;
int prev_id = 0;
float T_f;

std::ofstream outFile("../example.txt");
// double tau[12] = {-0.1, -0.1, 0.1, 0.1, 0.1, -0.1, 0.1, -0.1, 0.1, -0.1, 0.1, -0.1};
double tau[12] = {-0.2, -0.01, 0.015, 0.2, 0.01, -0.015, 0.2, -0.01, 0.015, -0.2, 0.01, -0.015};

// 处理12个角度！！！！！！！！！！！！！！！！！！！！
void udp_callback(uint32_t size, uint8_t *buffer, udp::RecvInfo info)
{
  if (info.flag == FLAG_SUCCESS)
  {
    for (j = 0; j < size; j++)
    {
      if (buffer[j] != ' ')
      {
        memset(id_ + j, buffer[j], 1);
      }
      else
      {
        i = j + 1;
        k = j + 1;
        break;
      }
    }
    memset(id_ + k - 1, '\0', 1);

    for (i; i < size; i++)
    {
      memset(pos_ + i - k, buffer[i], 1);
    }
    memset(pos_ + size - k, '\0', 1);
    ///////////
    if (std::stoi(id_) == 0)
    {
      cmd.id = 1;
      cmd.Pos = std::strtod(pos_, &endptr) * 6.33 + initial[0];
      cmd.T = T_f + tau[0];
      // cmd.Pos = std::strtod(pos_, &endptr);
      if (*endptr != '\0')
      {
        std::cerr << "Invalid part in string: " << std::endl;
      }
      outFile << "id:  " << cmd.id << "pos:  " << cmd.Pos << std::endl;
    }
    else if (std::stoi(id_) == 1)
    {
      cmd.id = 2;
      cmd.Pos = -std::strtod(pos_, &endptr) * 6.33 + initial[1];
      cmd.T = T_f + tau[1];
      // cmd.Pos = -std::strtod(pos_, &endptr);
      if (*endptr != '\0')
      {
        std::cerr << "Invalid part in string: " << std::endl;
      }
      outFile << "id:  " << cmd.id << "pos:  " << cmd.Pos << std::endl;
    }
    else if (std::stoi(id_) == 2)
    {
      cmd.id = 3;
      cmd.Pos = -std::strtod(pos_, &endptr) * 6.33 + initial[2];
      cmd.T = T_f + tau[2];
      // cmd.Pos = -std::strtod(pos_, &endptr);
      if (*endptr != '\0')
      {
        std::cerr << "Invalid part in string: " << std::endl;
      }
      outFile << "id:  " << cmd.id << "pos:  " << cmd.Pos << std::endl;
    }
    else if (std::stoi(id_) == 3)
    {
      cmd.id = 4;
      cmd.Pos = std::strtod(pos_, &endptr) * 6.33 + initial[3];
      cmd.T = T_f + tau[3];
      // cmd.Pos = std::strtod(pos_, &endptr);
      if (*endptr != '\0')
      {
        std::cerr << "Invalid part in string: " << std::endl;
      }
      outFile << "id:  " << cmd.id << "pos:  " << cmd.Pos << std::endl;
    }
    else if (std::stoi(id_) == 4)
    {
      cmd.id = 5;
      cmd.Pos = std::strtod(pos_, &endptr) * 6.33 + initial[4];
      cmd.T = T_f + tau[4];
      // cmd.Pos = std::strtod(pos_, &endptr);
      if (*endptr != '\0')
      {
        std::cerr << "Invalid part in string: " << std::endl;
      }
      outFile << "id:  " << cmd.id << "pos:  " << cmd.Pos << std::endl;
    }
    else if (std::stoi(id_) == 5)
    {
      cmd.id = 6;
      cmd.Pos = std::strtod(pos_, &endptr) * 6.33 + initial[5];
      cmd.T = T_f + tau[5];
      // cmd.Pos = std::strtod(pos_, &endptr);
      if (*endptr != '\0')
      {
        std::cerr << "Invalid part in string: " << std::endl;
      }
      outFile << "id:  " << cmd.id << "pos:  " << cmd.Pos << std::endl;
    }
    else if (std::stoi(id_) == 6)
    {
      cmd.id = 7;
      cmd.Pos = -std::strtod(pos_, &endptr) * 6.33 + initial[6];
      cmd.T = T_f + tau[6];
      // cmd.Pos = -std::strtod(pos_, &endptr);
      if (*endptr != '\0')
      {
        std::cerr << "Invalid part in string: " << std::endl;
      }
      outFile << "id:  " << cmd.id << "pos:  " << cmd.Pos << std::endl;
    }
    else if (std::stoi(id_) == 7)
    {
      cmd.id = 8;
      cmd.Pos = -std::strtod(pos_, &endptr) * 6.33 + initial[7];
      cmd.T = T_f + tau[7];
      // cmd.Pos = -std::strtod(pos_, &endptr);
      if (*endptr != '\0')
      {
        std::cerr << "Invalid part in string: " << std::endl;
      }
      outFile << "id:  " << cmd.id << "pos:  " << cmd.Pos << std::endl;
    }
    else if (std::stoi(id_) == 8)
    {
      cmd.id = 9;
      cmd.Pos = -std::strtod(pos_, &endptr) * 6.33 + initial[8];
      cmd.T = T_f + tau[8];
      // cmd.Pos = -std::strtod(pos_, &endptr);
      if (*endptr != '\0')
      {
        std::cerr << "Invalid part in string: " << std::endl;
      }
      outFile << "id:  " << cmd.id << "pos:  " << cmd.Pos << std::endl;
    }
    else if (std::stoi(id_) == 9)
    {
      cmd.id = 10;
      cmd.Pos = -std::strtod(pos_, &endptr) * 6.33 + initial[9];
      cmd.T = T_f + tau[9];
      // cmd.Pos = -std::strtod(pos_, &endptr);
      if (*endptr != '\0')
      {
        std::cerr << "Invalid part in string: " << std::endl;
      }
      outFile << "id:  " << cmd.id << "pos:  " << cmd.Pos << std::endl;
    }
    else if (std::stoi(id_) == 10)
    {
      cmd.id = 11;
      cmd.Pos = std::strtod(pos_, &endptr) * 6.33 + initial[10];
      cmd.T = T_f + tau[10];
      // cmd.Pos = std::strtod(pos_, &endptr);
      if (*endptr != '\0')
      {
        std::cerr << "Invalid part in string: " << std::endl;
      }
      outFile << "id:  " << cmd.id << "pos:  " << cmd.Pos << std::endl;
    }
    else if (std::stoi(id_) == 11)
    {
      cmd.id = 12;
      cmd.Pos = std::strtod(pos_, &endptr) * 6.33 + initial[11];
      cmd.T = T_f + tau[11];
      // cmd.Pos = std::strtod(pos_, &endptr);
      if (*endptr != '\0')
      {
        std::cerr << "Invalid part in string: " << std::endl;
      }
      outFile << "id:  " << cmd.id << "pos:  " << cmd.Pos << std::endl;
    }
  }
}

int main()
{
  udp_receiver.set_listen_port(UDP_LISTEN_PORT);
  udp_receiver.enable_async(udp_callback);

  if (udp_receiver.init() == true)
  {
    printf("初始化成功\n");
  }
  else
  {
    printf("%s %d\n", __FILE__, __LINE__);
    return 0;
  }

  cmd.motorType = MotorType::GO_M8010_6;
  cmd.mode = 1;
  cmd.K_P = 0.0;
  cmd.K_W = 0.0;
  cmd.Pos = 0.0;
  cmd.W = 0;
  cmd.T = 0.0;
  // cmd.id = 6;
  // serial.sendRecv(&cmd, &data);

  if (!get_initial_angle())
    return 0;
  cmd.K_P = 0.08;
  cmd.K_W = 0.01;

  while (true)
  {
    //  防止现实与目标角度差距太大
    if (abs(data.Pos / 6.33 - cmd.Pos / 6.33) > 0.5)
    {
      cmd.Pos = (cmd.Pos + data.Pos) / 6;
      serial.sendRecv(&cmd, &data);
      sleep(1.5);
    }
    //  摩擦力补偿
    // if (data.W > 0)
    //   T_f = (0.0187 + 0.0011 * data.W);
    // else if (data.W < 0)
    // {
    //   T_f = -0.0260 + 0.0011 * data.W;
    // }
    // else
    // {
    //   T_f = 0;
    // }

    // 发送数据
    serial.sendRecv(&cmd, &data);
    usleep(1000);
  }
  outFile.close();
  return 0;
}

bool get_initial_angle()
{
  for (int i = 0; i < 12; i++)
  {
    cmd.id = i + 1;
    serial.sendRecv(&cmd, &data);
    if (data.correct)
    {
      cmd.Pos = data.Pos;
      initial[i] = data.Pos;
    }
    else
    {
      std::cout << "data is not complete" << std::endl;
      return false;
    }
  }
  // cmd.id = 4;
  // cmd.mode = 1;
  // cmd.K_P = 0.0;
  // cmd.K_W = 0.0;
  // cmd.Pos = 0.0;
  // cmd.W = 0;
  // cmd.T = 0.0;
  // serial.sendRecv(&cmd, &data);
  // if (data.correct)
  // {
  //   cmd.Pos = data.Pos;
  //   initial[3] = data.Pos;
  // }
  // else
  // {
  //   std::cout << "data is not complete" << std::endl;
  //   return false;
  // }

  // cmd.id = 5;
  // cmd.mode = 1;
  // cmd.K_P = 0.0;
  // cmd.K_W = 0.0;
  // cmd.Pos = 0.0;
  // cmd.W = 0;
  // cmd.T = 0.0;
  // serial.sendRecv(&cmd, &data);
  // if (data.correct)
  // {
  //   cmd.Pos = data.Pos;
  //   initial[4] = data.Pos;
  // }
  // else
  // {
  //   std::cout << "data is not complete" << std::endl;
  //   return false;
  // }

  // cmd.id = 6;
  // cmd.mode = 1;
  // cmd.K_P = 0.0;
  // cmd.K_W = 0.0;
  // cmd.Pos = 0.0;
  // cmd.W = 0;
  // cmd.T = 0.0;
  // serial.sendRecv(&cmd, &data);
  // if (data.correct)
  // {
  //   cmd.Pos = data.Pos;
  //   initial[5] = data.Pos;
  // }
  // else
  // {
  //   std::cout << "data is not complete" << std::endl;
  //   return false;
  // }

  return true;
}