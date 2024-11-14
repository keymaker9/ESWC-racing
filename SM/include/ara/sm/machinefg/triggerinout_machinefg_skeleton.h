///////////////////////////////////////////////////////////////////////////////////////////////////////////
///                                                                                                        
/// Copyright, 2021 PopcornSAR Co., Ltd. All rights reserved.                                              
/// This software is copyright protected and proprietary to PopcornSAR Co., Ltd.                           
/// PopcornSAR Co., Ltd. grants to you only those rights as set out in the license conditions.             
///                                                                                                        
///////////////////////////////////////////////////////////////////////////////////////////////////////////
/// AUTOSAR VERSION                   : R20-11
/// GENERATED BY                      : PARA, ARA::COM Generator
///////////////////////////////////////////////////////////////////////////////////////////////////////////
/// GENERATED FILE NAME               : triggerinout_machinefg_skeleton.h
/// SERVICE INTERFACE NAME            : TriggerInOut_MachineFG
/// GENERATED DATE                    : 2024-08-14 09:44:01
///////////////////////////////////////////////////////////////////////////////////////////////////////////
///                                                                                                        
/// CAUTION!! AUTOMATICALLY GENERATED FILE - DO NOT EDIT                                                   
///                                                                                                        
///////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef PARA_COM_GEN_SERVICE_INTERFACE_TRIGGERINOUT_MACHINEFG_SKELETON_H
#define PARA_COM_GEN_SERVICE_INTERFACE_TRIGGERINOUT_MACHINEFG_SKELETON_H
///////////////////////////////////////////////////////////////////////////////////////////////////////////
/// INCLUSION HEADER FILES
///////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @uptrace{SWS_CM_01004}
#include "triggerinout_machinefg_common.h"
#include "para/com/skeleton/skeleton_interface.h"
/// @uptrace{SWS_CM_01005}
namespace ara
{
namespace sm
{
namespace machinefg
{
/// @uptrace{SWS_CM_01006}
namespace skeleton
{
class TriggerInOut_MachineFGSkeleton;
/// @uptrace{SWS_CM_01009}
namespace events
{
} /// namespace events
/// @uptrace{SWS_CM_01031}
namespace fields
{
/// @uptrace{SWS_CM_00007}
class Notifier
{
public:
    /// @brief Type alias for type of field value
    /// @uptrace{SWS_CM_00162, SWS_CM_90437}
    using FieldType = ara::sm::MachineStateType;
    /// @brief Constructor
    explicit Notifier(para::com::SkeletonInterface* interface) : mInterface(interface)
    {
    }
    /// @brief Destructor
    virtual ~Notifier() = default;
    /// @brief Delete copy constructor
    Notifier(const Notifier& other) = delete;
    /// @brief Delete copy assignment
    Notifier& operator=(const Notifier& other) = delete;
    /// @brief Move constructor
    Notifier(Notifier&& other) noexcept : mInterface(other.mInterface)
    {
        RegisterGetHandler(std::move(other.mGetHandler));
    }
    /// @brief Move assignment
    Notifier& operator=(Notifier&& other) noexcept
    {
        mInterface = other.mInterface;
        RegisterGetHandler(std::move(other.mGetHandler));
        return *this;
    }
    /// @brief Register callback for getter method
    /// @uptrace{SWS_CM_00114}
    ara::core::Result<void> RegisterGetHandler(std::function<ara::core::Future<FieldType>()> getHandler)
    {
        ara::core::Result<void> result{};
        if (getHandler != nullptr)
        {
            mGetHandler = std::move(getHandler);
            mInterface->SetMethodCallHandler(kGetterCallSign, [this](const std::vector<std::uint8_t>& data, const para::com::MethodToken token) {
                HandleGet(token);
            });
        }
        return result;
    }
    /// @brief Send notification with value to subscribing service consumers
    /// @uptrace{SWS_CM_90437}
    ara::core::Result<void> Update(const FieldType& value)
    {
        para::serializer::Serializer serializer{};
        serializer.write(value);
        auto payload = serializer.ensure();
        return mInterface->SendEvent(kNotifierCallSign, payload);
    }
    
private:
    void HandleGet(const para::com::MethodToken token)
    {
        std::uint8_t retResult{1};
        std::vector<std::uint8_t> retData{};
        auto future = mGetHandler();
        auto result = future.GetResult();
        if (result.HasValue())
        {
            FieldType value = result.Value();
            para::serializer::Serializer serializer{};
            serializer.write(value);
            retData = serializer.ensure();
            retResult = 0;
        }
        else
        {
            ara::core::ErrorDomain::IdType domainId = result.Error().Domain().Id();
            ara::core::ErrorDomain::CodeType errorCode = result.Error().Value();
            para::serializer::Serializer serializer{};
            serializer.write(0, true, 0, domainId);
            serializer.write(0, true, 0, errorCode);
            retData = serializer.ensure();
            retResult = 1;
        }
        mInterface->ReturnMethod(kGetterCallSign, retResult, retData, token);
    }
    para::com::SkeletonInterface* mInterface;
    std::function<ara::core::Future<FieldType>()> mGetHandler{nullptr};
    const std::string kGetterCallSign = {"NotifierGetter"};
    const std::string kNotifierCallSign = {"NotifierNotifier"};
};
/// @uptrace{SWS_CM_00007}
class Trigger
{
public:
    /// @brief Type alias for type of field value
    /// @uptrace{SWS_CM_00162, SWS_CM_90437}
    using FieldType = ara::sm::MachineStateType;
    /// @brief Constructor
    explicit Trigger(para::com::SkeletonInterface* interface) : mInterface(interface)
    {
    }
    /// @brief Destructor
    virtual ~Trigger() = default;
    /// @brief Delete copy constructor
    Trigger(const Trigger& other) = delete;
    /// @brief Delete copy assignment
    Trigger& operator=(const Trigger& other) = delete;
    /// @brief Move constructor
    Trigger(Trigger&& other) noexcept : mInterface(other.mInterface)
    {
        RegisterSetHandler(std::move(other.mSetHandler));
    }
    /// @brief Move assignment
    Trigger& operator=(Trigger&& other) noexcept
    {
        mInterface = other.mInterface;
        RegisterSetHandler(std::move(other.mSetHandler));
        return *this;
    }
    /// @brief Register callback for setter method
    /// @uptrace{SWS_CM_00116}
    ara::core::Result<void> RegisterSetHandler(std::function<ara::core::Future<FieldType>(const FieldType& value)> setHandler)
    {
        ara::core::Result<void> result;
        if (setHandler != nullptr)
        {
            mSetHandler = std::move(setHandler);
            mInterface->SetMethodCallHandler(kSetterCallSign, [this](const std::vector<std::uint8_t>& data, const para::com::MethodToken token) {
                HandleSet(data, token);
            });
        }
        return result;
    }
    
private:
    void HandleSet(const std::vector<std::uint8_t>& data, const para::com::MethodToken token)
    {
        std::uint8_t retResult{1};
        std::vector<std::uint8_t> retData{};
        para::serializer::Deserializer deserializer{data};
        fields::Trigger::FieldType _value_;
        deserializer.read(_value_);
        auto future = mSetHandler(_value_);
        auto result = future.GetResult();
        if (result.HasValue())
        {
            FieldType value = result.Value();
            para::serializer::Serializer serializer{};
            serializer.write(value);
            retData = serializer.ensure();
            retResult = 0;
        }
        else
        {
            ara::core::ErrorDomain::IdType domainId = result.Error().Domain().Id();
            ara::core::ErrorDomain::CodeType errorCode = result.Error().Value();
            para::serializer::Serializer serializer{};
            serializer.write(0, true, 0, domainId);
            serializer.write(0, true, 0, errorCode);
            retResult = 1;
        }
        mInterface->ReturnMethod(kSetterCallSign, retResult, retData, token);
    }
    para::com::SkeletonInterface* mInterface;
    std::function<ara::core::Future<FieldType>(const FieldType& value)> mSetHandler{nullptr};
    const std::string kSetterCallSign = {"TriggerSetter"};
};
} /// namespace fields
/// @uptrace{SWS_CM_00002}
class TriggerInOut_MachineFGSkeleton
{
public:
    /// @uptrace{SWS_CM_00191}
    /// @brief Constructor
    /// @uptrace{SWS_CM_00002, SWS_CM_00152}
    TriggerInOut_MachineFGSkeleton(ara::core::InstanceSpecifier instanceSpec, ara::com::MethodCallProcessingMode mode = ara::com::MethodCallProcessingMode::kEvent)
        : mInterface(std::make_unique<para::com::SkeletonInterface>(instanceSpec, mode))
        , Notifier(mInterface.get())
        , Trigger(mInterface.get())
    {
        mInterface->SetE2EErrorHandler([this](const ara::com::e2e::E2EErrorDomain& errorCode, ara::com::e2e::DataID dataID, ara::com::e2e::MessageCounter messageCounter) {
            E2EErrorHandler(errorCode, dataID, messageCounter);
        });
    }
    /// @brief Destructor
    virtual ~TriggerInOut_MachineFGSkeleton() = default;
    /// @brief Delete copy constructor
    /// @uptrace{SWS_CM_00134}
    TriggerInOut_MachineFGSkeleton(const TriggerInOut_MachineFGSkeleton& other) = delete;
    /// @brief Delete copy assignment
    /// @uptrace{SWS_CM_00134}
    TriggerInOut_MachineFGSkeleton& operator=(const TriggerInOut_MachineFGSkeleton& other) = delete;
    /// @brief Move constructor
    /// @uptrace{SWS_CM_00135}
    TriggerInOut_MachineFGSkeleton(TriggerInOut_MachineFGSkeleton&& other) noexcept
        : mInterface(std::move(other.mInterface))
        , Notifier(std::move(other.Notifier))
        , Trigger(std::move(other.Trigger))
    {
        mInterface->SetE2EErrorHandler([this](const ara::com::e2e::E2EErrorDomain& errorCode, ara::com::e2e::DataID dataID, ara::com::e2e::MessageCounter messageCounter) {
            E2EErrorHandler(errorCode, dataID, messageCounter);
        });
        other.mInterface.reset();
    }
    /// @brief Move assignment
    /// @uptrace{SWS_CM_00135}
    TriggerInOut_MachineFGSkeleton& operator=(TriggerInOut_MachineFGSkeleton&& other) noexcept
    {
        mInterface = std::move(other.mInterface);
        Notifier = std::move(other.Notifier);
        Trigger = std::move(other.Trigger);
        mInterface->SetE2EErrorHandler([this](const ara::com::e2e::E2EErrorDomain& errorCode, ara::com::e2e::DataID dataID, ara::com::e2e::MessageCounter messageCounter) {
            E2EErrorHandler(errorCode, dataID, messageCounter);
        });
        other.mInterface.reset();
        return *this;
    }
    /// @brief Send "OfferService" message to Communication Management
    /// @uptrace{SWS_CM_00101}
    ara::core::Result<void> OfferService()
    {
        return mInterface->OfferService();
    }
    /// @brief Send "StopOfferService" message to Communication Management
    /// @uptrace{SWS_CM_00111}
    void StopOfferService()
    {
        mInterface->StopOfferService();
    }
    /// @brief Allows the implementation providing the service method to trigger the execution of the next service consumer method call at a specific point of time
    ///        if the processing mode is set to kPoll.
    /// @note This function requires that ara::com::MethodCallProcessingMode is configured as kPoll by constructor
    /// @uptrace{SWS_CM_00199}
    ara::core::Future<bool> ProcessNextMethodCall()
    {
        ara::core::Promise<bool> promise{};
        auto ret = mInterface->ProcessNextMethodCall();
        if (ret.HasValue())
        {
            promise.set_value(ret.Value());
        }
        else
        {
            promise.SetError(ret.Error());
        }
        return promise.get_future();
    }
    /// @brief In case the call to E2E_check indicated a failed E2E check of the request message, the server application can get notified via an E2E error handler.
    /// @uptrace{SWS_CM_10470}
    virtual void E2EErrorHandler(const ara::com::e2e::E2EErrorDomain& errorCode, ara::com::e2e::DataID dataID, ara::com::e2e::MessageCounter messageCounter)
    {
    }
    
private:
    std::unique_ptr<para::com::SkeletonInterface> mInterface;
    
public:
    /// @brief Field, Notifier
    fields::Notifier Notifier;
    /// @brief Field, Trigger
    fields::Trigger Trigger;
    
private:
};
} /// namespace skeleton
} /// namespace machinefg
} /// namespace sm
} /// namespace ara
#endif /// PARA_COM_GEN_SERVICE_INTERFACE_TRIGGERINOUT_MACHINEFG_SKELETON_H