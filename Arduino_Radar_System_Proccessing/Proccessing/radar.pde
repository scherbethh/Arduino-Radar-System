import processing.serial.*;

Serial myPort;
String data = "";
int iAngle = 0, iDistance = 0;
PFont font;

void setup() {
  size(800, 600);
  myPort = new Serial(this, "COM3", 9600); // Seri iletişimi başlatır
  myPort.bufferUntil('.');
  font = createFont("Arial", 16, true);
  smooth(); // Daha yumuşak çizim için
}

void draw() {
  background(0);
  fill(98, 245, 31);
  textFont(font);
  translate(width / 2, height / 2);
  drawRadar();
  drawText();
}

void serialEvent(Serial myPort) {
  data = myPort.readStringUntil('.');
  if (data != null) {
    data = trim(data);
    int commaIndex = data.indexOf(',');
    if (commaIndex > 0) {
      String angle = data.substring(0, commaIndex);
      String distance = data.substring(commaIndex + 1);
      iAngle = parseInt(angle);
      iDistance = parseInt(distance);
    }
  }
}

void drawRadar() {
  // Radar dairelerini çiz
  strokeWeight(2);
  stroke(98, 245, 31);
  noFill();
  for (int radius = 100; radius <= 300; radius += 50) {
    ellipse(0, 0, radius * 2, radius * 2); // Çapı iki katına çıkararak yarıçapı 100, 150 ve 300 olarak ayarladık
  }

  // Radar açı çizgilerini çiz
  strokeWeight(1);
  for (int angle = 0; angle <= 180; angle += 30) {
    float x = cos(radians(angle)) * 300;
    float y = sin(radians(angle)) * 300;
    line(0, 0, x, -y);
  }

  // Algılanan nesneyi gösteren çizgiyi çiz
  if (iDistance > 0 && iDistance < 200) { // Mesafeyi 200 cm'den fazla olarak sınırladık
    float x = cos(radians(iAngle)) * iDistance * 1.5; // Ölçeği hassasiyet için değiştirdik
    float y = sin(radians(iAngle)) * iDistance * 1.5;
    stroke(255, 0, 0);
    strokeWeight(3);
    line(0, 0, x, -y);
    fill(255, 0, 0);
    ellipse(x, -y, 10, 10); // Algılanan nesne için bir nokta çiz
  }

  // Radar tarama çizgisi
  stroke(50, 255, 50, 150); // Yarı saydam yeşil
  strokeWeight(2);
  float scanX = cos(radians(iAngle)) * 300;
  float scanY = sin(radians(iAngle)) * 300;
  line(0, 0, scanX, -scanY);
}

void drawText() {
  fill(98, 245, 31);
  textAlign(LEFT);
  text("Angle: " + iAngle + "°", 10, height - 20);
  text("Distance: " + iDistance + " cm", 10, height - 40);

  // Radar açı etiketlerini çiz
  textAlign(CENTER);
  textSize(14);
  for (int angle = 0; angle <= 180; angle += 30) {
    float x = cos(radians(angle)) * 320;
    float y = sin(radians(angle)) * 320;
    fill(255);
    text(angle + "°", x, -y - 5);
  }
}
