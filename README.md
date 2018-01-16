# CarND-Controls-PID
Self-Driving Car Engineer Nanodegree Program

---

## Dependencies

* cmake >= 3.5
 * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1(mac, linux), 3.81(Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools]((https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)
* [uWebSockets](https://github.com/uWebSockets/uWebSockets)
  * Run either `./install-mac.sh` or `./install-ubuntu.sh`.
  * If you install from source, checkout to commit `e94b6e1`, i.e.
    ```
    git clone https://github.com/uWebSockets/uWebSockets 
    cd uWebSockets
    git checkout e94b6e1
    ```

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./pid`. 

## File structure

```
--- src/
 |-- main.cpp
 |-- PID.h
 |-- PID.cpp
 
```
 The main.cpp communicates with uWebSockets and calls PID controller to get a steering angel with the error computed.
 
 ## Reflection
 
 ### The effect each of the P, I, D component
 
* The gain function, KD, generates the derivative term. Note that the differential gain appears only in the feedback path. Such topology is common in controllers because it limits overshoot; in the forward path, a derivative term would likely produce a lot of overshoot in response to step (square wave) commands.

* The proportional gain, KP, in correct measure, provides stability as well as "growing room" for the other gains. If it gets too large, however, cover your ears because your machine is going to make a lot of noise. If it gets larger still, head for cover because the system will become unstable.

* The integral term KI is to make the system stiff and robust. In other words, a large KI makes it difficult for torque disturbances to move the shaft. Be careful, though, because the gain can become too large, generating a lot of overshoot.

### The selection of PID hyperparameters

It is well known that finding a perfect set of PID parameters is diffcult and it requires a lot of experience to tune the three parameters.

#### Parameters
The parameters I chose are [0.15, 0.0, 2.5]. It runs smoothly and stays on the track all the time.

I started from [0, 0, 0] and raised Kp first and Kd as well to see how it behaves. 
And I found it interesting that for this case, a PD controller work pretty well and I just stay with it.

#### Set up a bound for steering angel
Another trick I used is set a bound [-0.5, 0.5] for steering angle, just in case it moves too crazily

#### Relate throttle with steering angle
Setting the value of throttle inversely proportional to the steering angle guanranttes that when the vehicle needs to make a big turn, the speed should be relatively lower. 
And add a constant to the equation. Since the range of steering angle is [-0.5, 0.5], I just simply picked 0.6 as the constant. The result is acceptable.



