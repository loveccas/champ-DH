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
// double tau[12] = {-0.5, -0.1, 0.15, 0.5, 0.1, -0.15, 0.5, -0.1, 0.15, -0.5, 0.1, -0.15};
double tau[12] = {-0.5, -0.4, 0.0,
                  0.5, 0.4, -0.0,
                  0.5, -0.4, 0.0,
                  -0.5, 0.4, -0.0};

// 处理12个角度！！！！！！！！！！！！！！！！！！！！
void udp_callback(uint32_t size, uint8_t *buffer, udp::RecvInfo info)
{
  if (info.flag == FLAG_SUCCESS)
  {
    int m_id;
    double s;
    float percentage;
    // 调用 sscanf 解析数据并检查返回值
    if (std::sscanf(reinterpret_cast<char *>(buffer), "%d??%lf??%f", &m_id, &s, &percentage) == 3)
    {
      m_id++;
      cmd.id = m_id;

      if (percentage ==)
      {
      }
      else if ()
      {
      }
      // std::cout << "ID: " << m_id << ", Value: " << s << std::endl;
      cmd.Pos = s * 6.33 + initial[m_id - 1];
      if (abs(data.Pos / 6.33 - cmd.Pos / 6.33) > 0.5)
      {
        cmd.Pos = (cmd.Pos + data.Pos) / 6;
        printf("percentage%lf\n", percentage);
        goto fasong;
      }
      //  摩擦力补偿
      if (data.W > 0)
        T_f = (0.0187 + 0.0011 * data.W);
      else if (data.W < 0)
      {
        T_f = -0.0260 + 0.0011 * data.W;
      }
      else
      {
        T_f = 0;
      }
    // cmd.T = T_f + tau[m_id - 1];
    // serial.sendRecv(&cmd, &data);
    fasong:
      printf("percentage%lf\n", percentage);
      serial.sendRecv(&cmd, &data);
      // 发送数据
    }
    else
    {
      std::cerr << "Failed to parse data from buffer." << std::endl;
    }
  }
}

int main()
{

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

  while (1)
  {
    /* code */
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