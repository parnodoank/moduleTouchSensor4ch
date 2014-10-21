// moduleTouchSensor_2ch.ard


// 4ch Touch Sensor Module

// #With Alminium Sheet
//ハイパスフィルタの変数
//Default 10
int const N = 30; //200, 100 , 10, 300
int const D = 25;//Log of State

//この20という数字が大きければ鈍感に、小さければ敏感になります
//Default is 20
int const STD_TIME = 5; //10
// 100, 5 is better?


//For Storage LED condition
int a_state[D];
int b_state[D];
int c_state[D];
int d_state[D];


//Curve of touch
int a[N];
int b[N];
int c[N];
int d[N];


void setup(){

  //Init for sensor a-d
  for(int i=0; i<N; i++){

    a[i] = 0;
    b[i] = 0;
    c[i] = 0;
    d[i] = 0;

  }


  Serial.begin(9600);

  //IO For A
  //タッチパネル本体
  pinMode(13,OUTPUT);
  pinMode(12,INPUT);
  //確認用LED
  pinMode(5, OUTPUT);

  //IO for B
  //タッチパネル本体
  pinMode(11,OUTPUT);
  pinMode(10,INPUT);
  //確認用LED
  pinMode(4, OUTPUT);



  //IO for C
  //タッチパネル本体
  pinMode(9,OUTPUT);
  pinMode(8,INPUT);
  //確認用LED
  pinMode(3, OUTPUT);

/*
  //IO for D
  //タッチパネル本体
  pinMode(7,OUTPUT);
  pinMode(6,INPUT);
  //確認用LED
  pinMode(2, OUTPUT);  */

}

void loop(){

// Serial.println("foo");
  routine_a();
  routine_b();
  routine_c();
  routine_d();

}


void log_a (int num){

  for(int i=(D-1); i>=0; i--){

    a_state[i] = a_state[i-1];    

  }

  a_state[0] = num;

}

int chk_untouch_a (){

  int val = 0;
  for(int i =0; i<D; i++){

    val += a_state[i];

  }

  return val;

}

void routine_a ()
{


  //充電時間用の変数
  a[0] = 0;
  //一度HIGHにして
  digitalWrite(13, HIGH);

  //12番ピンがHIGHになるまで(=充電時間)をカウント
  while (digitalRead(12)!=HIGH){
    a[0]++;
  }
  //LOWに戻す
  digitalWrite(13, LOW);

  //たまに値がぶれるのでローパスフィルタをかける。
  float ave = 0;
  for(int i=0; i<N; i++){
    ave += a[i];
  }
  ave /= N;


  //この20という数字が大きければ鈍感に、小さければ敏感になります
  //Default is 20
  if(ave > STD_TIME){

    if(a_state[0] == 0){
      log_a(1); //Set the record
      digitalWrite(5, HIGH);
      Serial.println("touch:A");
    }

    //   log_a(1); //Set the record
    // if(chk_untouch_a() == D){
    //   log_a(1); //Set the record
    //   digitalWrite(5, HIGH);
    //   Serial.println("touch:A");
    // }



  }else{
      // log_a(0); //Set the record
        // digitalWrite(5, LOW);

      log_a(0); //Set the record
      if(chk_untouch_a()==0){
        digitalWrite(5, LOW);
      }
  }

  //変数をずらす。
  for(int i=(N-1); i>=0; i--){
    a[i] = a[i-1];    
  }

}


void routine_b ()
{

  //充電時間用の変数
  b[0] = 0;
  //一度HIGHにして
  digitalWrite(11, HIGH);

  //12番ピンがHIGHになるまで(=充電時間)をカウント
  while (digitalRead(10)!=HIGH){
    b[0]++;
  }
  //LOWに戻す
  digitalWrite(11, LOW);

  //たまに値がぶれるのでローパスフィルタをかける。
  float ave = 0;
  for(int i=0; i<N; i++){
    ave += b[i];
  }
  ave /= N;

  //この20という数字が大きければ鈍感に、小さければ敏感になります
  //Default is 20
  if(ave > STD_TIME){
    if(b_state[0] == 0){
      digitalWrite(4, HIGH);
      Serial.println("touch:B");
      b_state[0] = 1;
    }

  }else{
    digitalWrite(4, LOW);
    b_state[0] = 0;
  }

  //変数をずらす。
  for(int i=(N-1); i>=0; i--){
    b[i] = b[i-1];    
  }

}


void routine_c ()
{

  //充電時間用の変数
  c[0] = 0;
  //一度HIGHにして
  digitalWrite(9, HIGH);

  //12番ピンがHIGHになるまで(=充電時間)をカウント
  while (digitalRead(8)!=HIGH){
    c[0]++;
  }
  //LOWに戻す
  digitalWrite(9, LOW);

  //たまに値がぶれるのでローパスフィルタをかける。
  float ave = 0;
  for(int i=0; i<N; i++){
    ave += c[i];
  }
  ave /= N;

  //この20という数字が大きければ鈍感に、小さければ敏感になります
  //Default is 20
  if(ave > STD_TIME){

    if(c_state[0] == 0){
      digitalWrite(3, HIGH);
      Serial.println("touch:C");
      c_state[0] = 1;
    }

  }else{
    c_state[0] = 0;
    digitalWrite(3, LOW);
  }

  //変数をずらす。
  for(int i=(N-1); i>=0; i--){
    c[i] = c[i-1];    
  }

}


void routine_d ()
{

  //充電時間用の変数
  d[0] = 0;
  //一度HIGHにして
  digitalWrite(7, HIGH);

  //12番ピンがHIGHになるまで(=充電時間)をカウント
  while (digitalRead(6)!=HIGH){
    d[0]++;
  }
  //LOWに戻す
  digitalWrite(7, LOW);

  //たまに値がぶれるのでローパスフィルタをかける。
  float ave = 0;
  for(int i=0; i<N; i++){
    ave += d[i];
  }
  ave /= N;


  //この20という数字が大きければ鈍感に、小さければ敏感になります
  //Default is 20
  if(ave > STD_TIME){
    if(d_state[0] == 0){
      digitalWrite(2, HIGH);
      Serial.println("touch:D2");
      d_state[0] = 1;
    }
  }else{
    digitalWrite(2, LOW);
    d_state[0] = 0;
  }

  //変数をずらす。
  for(int i=(N-1); i>=0; i--){
    d[i] = d[i-1];    
  }

}
