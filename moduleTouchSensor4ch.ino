// moduleTouchSensor_2ch.ard


// 4ch Touch Sensor Module

// #With Alminium Sheet
//ハイパスフィルタの変数
//Default 10
int const N = 300; //300

//この20という数字が大きければ鈍感に、小さければ敏感になります
//Default is 20
int const STD_TIME = 7; //10
// 100, 5 is better?


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

  //IO for D
  //タッチパネル本体
  pinMode(7,OUTPUT);
  pinMode(6,INPUT);
  //確認用LED
  pinMode(2, OUTPUT);  

}
 
void loop(){

  routine_a();
  routine_b();
//  routine_c();
//  routine_d();

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
 
  //値チェック
  Serial.print("a:");  
  Serial.println(a[0]);
 
  //この20という数字が大きければ鈍感に、小さければ敏感になります
  //Default is 20
  if(ave > STD_TIME){
    digitalWrite(5, HIGH);
    Serial.println("touch");
  }else{
    digitalWrite(5, LOW);
  }
 
  //変数をずらす。
  for(int i=0; i<N-1; i++){
    a[i+1] = a[i];
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
 
  //値チェック
  Serial.print("b:");  
  Serial.println(b[0]);
 
  //この20という数字が大きければ鈍感に、小さければ敏感になります
  //Default is 20
  if(ave > STD_TIME){
    digitalWrite(4, HIGH);
  }else{
    digitalWrite(4, LOW);
  }
 
  //変数をずらす。
  for(int i=0; i<N-1; i++){
    b[i+1] = b[i];
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
 
  //値チェック
  Serial.print("a:");  
  Serial.println(a[0]);
 
  //この20という数字が大きければ鈍感に、小さければ敏感になります
  //Default is 20
  if(ave > STD_TIME){
    digitalWrite(3, HIGH);
    Serial.println("touch");
  }else{
    digitalWrite(3, LOW);
  }
 
  //変数をずらす。
  for(int i=0; i<N-1; i++){
    c[i+1] = c[i];
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
 
  //値チェック
  Serial.print("a:");  
  Serial.println(a[0]);
 
  //この20という数字が大きければ鈍感に、小さければ敏感になります
  //Default is 20
  if(ave > STD_TIME){
    digitalWrite(2, HIGH);
    Serial.println("touch");
  }else{
    digitalWrite(2, LOW);
  }
 
  //変数をずらす。
  for(int i=0; i<N-1; i++){
    d[i+1] = d[i];
  }  
  
}

