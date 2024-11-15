///////////////////////////////////////////////////////////////////////////////////////////////////////////
///                                                                                                        
/// Copyright, 2021 PopcornSAR Co., Ltd. All rights reserved.                                              
/// This software is copyright protected and proprietary to PopcornSAR Co., Ltd.                           
/// PopcornSAR Co., Ltd. grants to you only those rights as set out in the license conditions.             
///                                                                                                        
///////////////////////////////////////////////////////////////////////////////////////////////////////////
/// AUTOSAR VERSION                   : R20-11
/// GENERATED BY                      : PARA, Adaptive Application Generator
///////////////////////////////////////////////////////////////////////////////////////////////////////////
/// GENERATED FILE NAME               : actuator.cpp
/// SOFTWARE COMPONENT NAME           : Actuator
/// GENERATED DATE                    : 2024-08-14 09:44:02
///////////////////////////////////////////////////////////////////////////////////////////////////////////
/// INCLUSION HEADER FILES
///////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "actuator/aa/actuator.h"
 
namespace actuator
{
namespace aa
{
 
Actuator::Actuator()
    : m_logger(ara::log::CreateLogger("ACTR", "SWC", ara::log::LogLevel::kVerbose))
    , m_workers(1) // m_workers.Async에 등록가능한 함수 갯수
{
}
 
Actuator::~Actuator()
{
}

// Actuator Software Component의 초기화 함수.
// 설계하였던 Port 객체들을 생성한다.
bool Actuator::Initialize()
{
    m_logger.LogInfo() << "Actuator::Initialize";
    
    bool init{true};

    // ControlData RPort 객체의 생성
    m_ControlData = std::make_shared<actuator::aa::port::ControlData>();
    
    return init;
}

// Actuator Software Component의 시작 함수
void Actuator::Start()
{
    m_logger.LogInfo() << "Actuator::Start";

    // ControlData RPort 의 Start() 함수를 호출한다.
    m_ControlData->Start();
    
    // run software component
    Run();
}

// Actuator가 종료되어야 할때 호출되는 함수.
void Actuator::Terminate()
{
    m_logger.LogInfo() << "Actuator::Terminate";

    // ControlData RPort 에 대한 Terminate() 함수를 호출한다.
    m_ControlData->Terminate();
}

// Actuator Software Component의 수행 함수
void Actuator::Run()
{
    m_logger.LogInfo() << "Actuator::Run";

    // 수행해야 할 작업에 대해 m_workers.Async() 호출을 통해 등록한다.
    m_workers.Async([this] { TaskReceiveCEventCyclic(); });

    // 위의 Async로 등록된 함수들이 모두 리턴될때까지 기다린다.
    m_workers.Wait();
}

// ControlData CEvent의 Cyclic 수신처리에 대한 수행
void Actuator::TaskReceiveCEventCyclic()
{
    m_ControlData->SetReceiveEventCEventHandler([this](const auto& sample)
    {
        OnReceiveCEvent(sample);
    });
    m_ControlData->ReceiveEventCEventCyclic();
}

// ControlData CEvent를 받았을시의 처리 함수
void Actuator::OnReceiveCEvent(const deepracer::service::controldata::proxy::events::CEvent::SampleType& sample)
{
    m_logger.LogInfo() << "Actuator::OnReceiveCEvent:" << sample;
}
 
} /// namespace aa
} /// namespace actuator
