#ifndef BALANCE_H
#define BALANCE_H


typedef struct PID
{ 
  float Pro;
  float Int;
  float Der;
  float TarVal;//Ŀ��ֵ
  float StaVal;//״ֵ̬
  float Error;//��ǰ���
  float LastErr;//�ϴ����
  float PreErr;//���ϴ����
} PID;




double PID_Position (PID *pid , int TarVal , int StaVal);
#endif	/* BALANCE_H */

