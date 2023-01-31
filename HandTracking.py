import cv2
import serial
from cvzone.HandTrackingModule import HandDetector

ser = serial.Serial('COM3', 9600, timeout=1)  
cap = cv2.VideoCapture(0)
cv2.namedWindow("Image", cv2.WINDOW_NORMAL)
cv2.setWindowProperty("Image", cv2.WND_PROP_FULLSCREEN, cv2.WINDOW_FULLSCREEN)
detector = HandDetector(detectionCon=0.8, maxHands=1)

while True:
    success, img = cap.read()
    hands, img = detector.findHands(img) 

    if hands:
        hand1 = hands[0]
        lmList1 = hand1["lmList"] 
        bbox1 = hand1["bbox"]
        centerPoint1 = hand1['center'] 
        handType1 = hand1["type"] 

        fingers1 = detector.fingersUp(hand1)
        fingers_data = ''.join(str(f) for f in fingers1)
        ser.write(('$' + fingers_data).encode())
        print(fingers1)

    cv2.imshow("Image", img)
    key = cv2.waitKey(1)
    if key == ord('q'):
        ser.close() 
        break

cap.release()
cv2.destroyAllWindows()
