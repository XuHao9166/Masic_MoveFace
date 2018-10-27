# Masic_MoveFace

依赖库：opencv2411及以上、Dlib19.7 

主要的算法步骤：

1、经过人脸检测算法检测出人脸关键点
2、在视频当前帧图像上进行马赛克生成映射
3、根据人脸关键点的位置获得人脸包络
4、由人脸包络生成掩码图
5、将掩码图和马赛克图结合生成最终的动态人脸马赛克图像

depend lib:opencv2411or up、Dlib19.7 or up

The main algorithm steps:

1, through the face detection algorithm to detect the key points of the face
2. Perform mosaic generation mapping on the current frame image of the video.
3. Obtain the face envelope according to the position of the key point of the face
4, by the face envelope generation mask map
5. Combine the mask map and the mosaic map to generate the final dynamic face mosaic image.




