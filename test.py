#############################################################
# This program will open a camera for use of a Computer
# Vision face detection program to output into
# an arduino with the locations and number of faces
#############################################################
import time
import cv2
from cvzone.FaceDetectionModule import FaceDetector
from cvzone.SerialModule import SerialObject

cap = cv2.VideoCapture(0)
detector = FaceDetector()
arduino = SerialObject()

while True:
    # get image data
    success, img = cap.read()
    img, bboxs = detector.findFaces(img)
    # i is distance from camera
    # people is faces faces in veiw of camera

    # 3 buffer digits 3 digits for left 3 digits for right
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
            #200 is middle of camera
            if(x>200):
                if(w>maxright):
                    maxright=w
                people+=1
            else:
                if (w > maxleft):
                    maxleft = w
                people+=1000
            count+=1

    i+=maxleft+(maxright*1000)
    arduino.sendData([i,people])

    cv2.imshow("Image", img)
    # terminate condition
    if cv2.waitKey(1) & 0xFF == ord('q') or cv2.getWindowProperty("Image", cv2.WND_PROP_VISIBLE) < 1:
        arduino.sendData([111000000111000000])

        break
cap.release()
cv2.destroyAllWindows()