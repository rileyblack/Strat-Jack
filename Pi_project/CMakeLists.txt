cmake_minimum_required(VERSION 2.8)
project( PiProject )
find_package( OpenCV REQUIRED )
add_executable( PiProject BlackJack.cpp  CameraFeed.cpp  Card.cpp  CardDetector.cpp  Dealer.cpp  Hand.cpp  main.cpp  Strategy.cpp  User.cpp )
target_link_libraries( PiProject ${REQUIRED_LIBRARIES} ${OpenCV_LIBS} )


