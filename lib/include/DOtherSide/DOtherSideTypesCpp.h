#pragma once

#include <QtCore/QString>
#include <QtCore/QMetaType>

#include "DOtherSide/DOtherSideTypes.h"
#include "DOtherSide/Utils.h"

namespace DOS
{
struct SignalDefinition
{
    SignalDefinition(QString n,
                     std::vector<QMetaType::Type> v)
        : name(std::move(n))
        , parameterTypes(std::move(v))
    {}

    SignalDefinition(::SignalDefinition cType)
        : name(QString::fromUtf8(cType.name))
    {
        auto wrapped = wrap_array(cType.parametersMetaTypes, cType.parametersCount);
        auto conversion = [](int type)->QMetaType::Type { return static_cast<QMetaType::Type>(type);};
        std::transform(wrapped.begin(), wrapped.end(), parameterTypes.begin(), conversion);
    }

    QString name;
    std::vector<QMetaType::Type> parameterTypes;
};

struct SlotDefinition
{
    SlotDefinition(QString n,
                   QMetaType::Type t,
                   std::vector<QMetaType::Type> v)
        : name(std::move(n))
        , returnType(std::move(t))
        , parameterTypes(std::move(v))
    {}

    SlotDefinition(::SlotDefinition cType)
        : name(QString::fromUtf8(cType.name))
        , returnType(static_cast<QMetaType::Type>(cType.returnMetaType))
    {
        auto wrapped = wrap_array(cType.parametersMetaTypes, cType.parametersCount);
        auto conversion = [](int type)->QMetaType::Type { return static_cast<QMetaType::Type>(type);};
        std::transform(wrapped.begin(), wrapped.end(), parameterTypes.begin(), conversion);
    }

    QString name;
    QMetaType::Type returnType;
    std::vector<QMetaType::Type> parameterTypes;
};

struct PropertyDefinition
{
    PropertyDefinition(QString n,
                       QMetaType::Type t,
                       QString r,
                       QString w,
                       QString s)
        : name(std::move(n))
        , type(std::move(t))
        , readSlot(std::move(r))
        , writeSlot(std::move(w))
        , notifySignal(std::move(s))
    {}

    PropertyDefinition(::PropertyDefinition cType)
        : name(cType.name)
        , type(static_cast<QMetaType::Type>(cType.propertyMetaType))
        , readSlot(QString::fromUtf8(cType.readSlot))
        , writeSlot(QString::fromUtf8(cType.writeSlot))
        , notifySignal(QString::fromUtf8(cType.notifySignal))
    {}

    QString name;
    QMetaType::Type type;
    QString readSlot;
    QString writeSlot;
    QString notifySignal;
};

using SignalDefinitions = std::vector<SignalDefinition>;
using SlotDefinitions = std::vector<SlotDefinition>;
using PropertyDefinitions = std::vector<PropertyDefinition>;

SignalDefinitions toVector(const ::SignalDefinitions& cType);
SlotDefinitions toVector(const ::SlotDefinitions& cType);
PropertyDefinitions toVector(const ::PropertyDefinitions& cType);

}