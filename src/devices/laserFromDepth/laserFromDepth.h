/*
 * SPDX-FileCopyrightText: 2006-2021 Istituto Italiano di Tecnologia (IIT)
 * SPDX-License-Identifier: LGPL-2.1-or-later
 */

#ifndef LASER_FROM_DEPTH_H
#define LASER_FROM_DEPTH_H

#include <yarp/os/PeriodicThread.h>
#include <yarp/os/Semaphore.h>
#include <yarp/dev/ControlBoardInterfaces.h>
#include <yarp/dev/IRangefinder2D.h>
#include <yarp/dev/PolyDriver.h>
#include <yarp/sig/Vector.h>
#include <yarp/dev/IRGBDSensor.h>
#include <yarp/dev/Lidar2DDeviceBase.h>

#include <mutex>
#include <string>
#include <vector>

using namespace yarp::os;
using namespace yarp::dev;

typedef unsigned char byte;

//---------------------------------------------------------------------------------------------------------------
/**
 * @ingroup dev_impl_lidar
 *
 * \brief `laserFromDepth`: This devices connects to an RGBDSensor_nws_yarp to receive depth data.
 * Data is then processed and exposed as a lidar device exposing a IRangefinder2D interface.
 */
class LaserFromDepth : public PeriodicThread, public yarp::dev::Lidar2DDeviceBase, public DeviceDriver
{
protected:
    PolyDriver driver;
    IRGBDSensor* iRGBD = nullptr;

    size_t m_depth_width = 0;
    size_t m_depth_height = 0;
    yarp::sig::ImageOf<float> m_depth_image;

public:
    LaserFromDepth(double period = 0.01) : PeriodicThread(period),
        Lidar2DDeviceBase()
    {}

    ~LaserFromDepth()
    {
    }

    bool open(yarp::os::Searchable& config) override;
    bool close() override;
    bool threadInit() override;
    void threadRelease() override;
    void run() override;

public:
    //IRangefinder2D interface
    yarp::dev::ReturnValue setDistanceRange    (double min, double max) override;
    yarp::dev::ReturnValue setScanLimits        (double min, double max) override;
    yarp::dev::ReturnValue setHorizontalResolution      (double step) override;
    yarp::dev::ReturnValue setScanRate         (double rate) override;

public:
    //Lidar2DDeviceBase
    bool acquireDataFromHW() override final;
};

#endif
