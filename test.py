import time

import cv2
from cvzone.FaceDetectionModule import FaceDetector
from cvzone.SerialModule import SerialObject

cap = cv2.VideoCapture(0)
detector = FaceDetector()
arduino = SerialObject()

while True:
    success, img = cap.read()
    img, bboxs = detector.findFaces(img)
    i=111000000
    people=111000000
    count=0
    maxright=0
    maxleft=0
    if bboxs:
        for bbox in bboxs:
            # bbox['bbox'] contains [x, y, w, h]
            x, y, w, h = bbox['bbox']
            w=int((w))
            if(x>200):
                if(w>maxright):
                    maxright=w
                people+=1
            else:
                if (w > maxleft):
                    maxleft = w
                people+=1000
            # Print the x and y coordinates
            count+=1

    i+=maxleft+(maxright*1000)
    arduino.sendData([i,people])

    cv2.imshow("Image", img)
    if cv2.waitKey(1) & 0xFF == ord('q') or cv2.getWindowProperty("Image", cv2.WND_PROP_VISIBLE) < 1:
        arduino.sendData([111000000111000000])

        break
cap.release()
cv2.destroyAllWindows()