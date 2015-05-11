import cv2
import numpy as np

#WARNING! OpenCV 3.* required.

# Parameters for lucas kanade optical flow
lk_params = dict( winSize  = (15,15),
                  maxLevel = 2,
                  criteria = (cv2.TERM_CRITERIA_EPS | cv2.TERM_CRITERIA_COUNT, 10, 0.03))


def getHarrisPoints(gray_img):
    harris = cv2.cornerHarris(gray_img, 2, 3, 0.05)
    # Threshold for an optimal value
    xarr,yarr = np.nonzero(harris > 0.03*harris.max())
    harrisPointsArray = [np.array([[x,y]]) for x,y in zip(xarr,yarr)]
    return np.array(harrisPointsArray, dtype=np.float32)


def getFASTPoints(gray_img):
    # Initiate FAST object with default values
    fast = cv2.FastFeatureDetector_create(threshold=5)
    # find keypoints
    kp_array = fast.detect(gray_img,None)
    # print kp_array[0].pt[1]
    fastPointsArray = [np.array([[kp.pt[0], kp.pt[1]]]) for kp in kp_array]
    return np.array(fastPointsArray, dtype=np.float32)

def videoTracking(cap, slow_motion_delay, detector):
    # Create some random colors
    color = np.random.randint(0,255,(100,3))
    # Take first frame and find corners in it
    ret, old_frame = cap.read()
    old_gray = cv2.cvtColor(old_frame, cv2.COLOR_BGR2GRAY)
    # Create a mask image for drawing purposes
    mask = np.zeros_like(old_frame)
    # Define the codec and create VideoWriter object
    # height, width, _ = old_frame.shape
    # fourcc = cv2.VideoWriter_fourcc(*'XVID')
    # out = cv2.VideoWriter('output_'+detector+'.avi',fourcc, slow_motion_delay, (width,height))
    if detector == 'Harris':
        oldTrackPoints = getHarrisPoints(old_gray)
    elif detector == 'FAST':
        oldTrackPoints = getFASTPoints(old_gray)
    else:
        print('Not correct method')
    print "$$$ Checking if i can recognise your move, n1ggv"
    while not len(oldTrackPoints) and cap.isOpened():
        ret, old_frame = cap.read()
        old_gray = cv2.cvtColor(old_frame, cv2.COLOR_BGR2GRAY)
        oldTrackPoints = getFASTPoints(old_gray)
    while cap.isOpened():
        ret, frame = cap.read()
        track_img = None
        if ret:
            new_gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
            # calculate optical flow
            newTrackPoints, st, err = cv2.calcOpticalFlowPyrLK(old_gray, new_gray, oldTrackPoints,
                                                               None, **lk_params)

            # Select good points
            if newTrackPoints is not None and len(newTrackPoints):
                good_new = newTrackPoints[st==1]
                good_old = oldTrackPoints[st==1]
                # draw the tracks
                for i,(new,old) in enumerate(zip(good_new,good_old)):
                    a,b = new.ravel()
                    c,d = old.ravel()
                    mask = cv2.line(mask, (a,b),(c,d),color[i%len(color)].tolist(), 2) #(255,0,0), 2)
                    frame = cv2.circle(frame,(a,b),2,color[i%len(color)].tolist(),-1)#(0,255,0),-1)
                track_img = cv2.add(frame, mask)
                #write tracked frame
                # out.write(track_img)
                # cv2.imshow('videoTracking '+detector, track_img)
                # if cv2.waitKey(slow_motion_delay) & 0xFF == ord('q'):
                #     break

                # Now update the previous frame and previous points
                old_gray = new_gray.copy()
                oldTrackPoints = good_new.reshape(-1,1,2)
        else:
            break
    return mask

def crop_image(input_img):
    sum_rows = np.sum(input_img, axis=0)
    nonnull = np.nonzero(sum_rows)[0]
    left = nonnull[0]
    right = nonnull[len(nonnull)-1]
    sum_cols = np.sum(input_img, axis=1)
    nonnull = np.nonzero(sum_cols)[0]
    low = nonnull[0]
    high = nonnull[len(nonnull)-1]
    return input_img[low:high,left:right]


def normalize_img(mask_img):
    print "$$$ Be good, my beach"
    normalized_img = cv2.cvtColor(mask_img, cv2.COLOR_BGR2GRAY)
    _,thresh_img = cv2.threshold(normalized_img, 0, 255, cv2.THRESH_BINARY)
    kernel = np.ones((5,5),dtype=np.uint8)
    dilated_img = cv2.dilate(thresh_img, kernel)
    dilated_img = crop_image(dilated_img)
    height, width = dilated_img.shape
    dilated_img = cv2.resize(dilated_img, (800,1143))
    # delta_y = (1143 - dilated_img.shape[0])/2
    # delta_y = delta_y  if delta_y > 0 else 0
    # delta_x = (808 - dilated_img.shape[1])/2
    # delta_x = delta_x  if delta_x > 0 else 0
    # dilated_img = cv2.copyMakeBorder(dilated_img,delta_y,delta_y,delta_x,delta_x,cv2.BORDER_CONSTANT,value=0)
    return dilated_img


def detectIt(video, letter):
    cap = cv2.VideoCapture(video)
    try:
        #slow_motion_delay in milliseconds
        slow_motion_delay = 80
        print "$$$~ Brick Squad Monopoly security ~$$$"
        mask_img = videoTracking(cap, slow_motion_delay, 'FAST')
        print "$$$ U can't hide u can't run."
        cap.release()
        cv2.imshow('mask_img', mask_img)
        normalized_img = normalize_img(mask_img)
        print "$$$ Here we watch ya."
        let_symbol = cv2.imread("symbol_{0}.jpg".format(letter))
        let_symbol = cv2.cvtColor(let_symbol, cv2.COLOR_BGR2GRAY)
        _, let_symbol = cv2.threshold(let_symbol, 0, 255, cv2.THRESH_BINARY_INV)
        let_symbol = crop_image(let_symbol)
        _,let_symbol = cv2.threshold(let_symbol, 0, 255, cv2.THRESH_BINARY_INV)
        #Good size for us
        let_symbol = cv2.resize(let_symbol,(800,1143))
        # cv2.imshow('let_symbol', let_symbol)
        # cv2.imshow('normalized_img', normalized_img)
        result_img = cv2.bitwise_and(normalized_img, normalized_img, mask=let_symbol)
        # cv2.imshow('result_img', result_img)
        # cv2.waitKey(0)
        # cv2.destroyAllWindows()
        if np.sum(result_img) < 0.15 * 255 * 800 * 1143:
            print "$$$ Br0! You are masta!"
            return True
        print "$$$ Waka Fl0cka doesn't like it! Get the float of the property!"
        return False
    except:
        print "$$$ Get OpenCV 3 or die tryin'."
        cap.release()
        return False
        

if __name__ == "__main__":
    #Test purposes
    filename = "test_L.avi"
    detectIt(filename, "L")
