/*
 *  Copyright (C) 2020-2021 Embedded AMS B.V. - All Rights Reserved
 *
 *  This file is part of Embedded Proto.
 *
 *  Embedded Proto is open source software: you can redistribute it and/or
 *  modify it under the terms of the GNU General Public License as published
 *  by the Free Software Foundation, version 3 of the license.
 *
 *  Embedded Proto  is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with Embedded Proto. If not, see <https://www.gnu.org/licenses/>.
 *
 *  For commercial and closed source application please visit:
 *  <https://EmbeddedProto.com/license/>.
 *
 *  Embedded AMS B.V.
 *  Info:
 *    info at EmbeddedProto dot com
 *
 *  Postal address:
 *    Johan Huizingalaan 763a
 *    1066 VH, Amsterdam
 *    the Netherlands
 */

// This file is generated. Please do not edit!
#ifndef IOBOARDCOMMUNICATIONUP_H
#define IOBOARDCOMMUNICATIONUP_H

#include <cstdint>
#include <MessageInterface.h>
#include <WireFormatter.h>
#include <Fields.h>
#include <MessageSizeCalculator.h>
#include <ReadBufferSection.h>
#include <RepeatedFieldFixedSize.h>
#include <FieldStringBytes.h>
#include <Errors.h>
#include <limits>

// Include external proto definitions


class ArmStatus final: public ::EmbeddedProto::MessageInterface
{
  public:
    ArmStatus() = default;
    ArmStatus(const ArmStatus& rhs )
    {
      set_z_prismatic_position(rhs.get_z_prismatic_position());
      set_z_rotational_position(rhs.get_z_rotational_position());
      set_y_rotational_position(rhs.get_y_rotational_position());
      set_pumpEnabled(rhs.get_pumpEnabled());
      set_valveClosed(rhs.get_valveClosed());
      set_pressureValue(rhs.get_pressureValue());
    }

    ArmStatus(const ArmStatus&& rhs ) noexcept
    {
      set_z_prismatic_position(rhs.get_z_prismatic_position());
      set_z_rotational_position(rhs.get_z_rotational_position());
      set_y_rotational_position(rhs.get_y_rotational_position());
      set_pumpEnabled(rhs.get_pumpEnabled());
      set_valveClosed(rhs.get_valveClosed());
      set_pressureValue(rhs.get_pressureValue());
    }

    ~ArmStatus() override = default;

    enum class id : uint32_t
    {
      NOT_SET = 0,
      Z_PRISMATIC_POSITION = 1,
      Z_ROTATIONAL_POSITION = 2,
      Y_ROTATIONAL_POSITION = 3,
      PUMPENABLED = 4,
      VALVECLOSED = 5,
      PRESSUREVALUE = 6
    };

    ArmStatus& operator=(const ArmStatus& rhs)
    {
      set_z_prismatic_position(rhs.get_z_prismatic_position());
      set_z_rotational_position(rhs.get_z_rotational_position());
      set_y_rotational_position(rhs.get_y_rotational_position());
      set_pumpEnabled(rhs.get_pumpEnabled());
      set_valveClosed(rhs.get_valveClosed());
      set_pressureValue(rhs.get_pressureValue());
      return *this;
    }

    ArmStatus& operator=(const ArmStatus&& rhs) noexcept
    {
      set_z_prismatic_position(rhs.get_z_prismatic_position());
      set_z_rotational_position(rhs.get_z_rotational_position());
      set_y_rotational_position(rhs.get_y_rotational_position());
      set_pumpEnabled(rhs.get_pumpEnabled());
      set_valveClosed(rhs.get_valveClosed());
      set_pressureValue(rhs.get_pressureValue());
      return *this;
    }

    inline void clear_z_prismatic_position() { z_prismatic_position_.clear(); }
    inline void set_z_prismatic_position(const EmbeddedProto::uint32& value) { z_prismatic_position_ = value; }
    inline void set_z_prismatic_position(const EmbeddedProto::uint32&& value) { z_prismatic_position_ = value; }
    inline EmbeddedProto::uint32& mutable_z_prismatic_position() { return z_prismatic_position_; }
    inline const EmbeddedProto::uint32& get_z_prismatic_position() const { return z_prismatic_position_; }
    inline EmbeddedProto::uint32::FIELD_TYPE z_prismatic_position() const { return z_prismatic_position_.get(); }

    inline void clear_z_rotational_position() { z_rotational_position_.clear(); }
    inline void set_z_rotational_position(const EmbeddedProto::uint32& value) { z_rotational_position_ = value; }
    inline void set_z_rotational_position(const EmbeddedProto::uint32&& value) { z_rotational_position_ = value; }
    inline EmbeddedProto::uint32& mutable_z_rotational_position() { return z_rotational_position_; }
    inline const EmbeddedProto::uint32& get_z_rotational_position() const { return z_rotational_position_; }
    inline EmbeddedProto::uint32::FIELD_TYPE z_rotational_position() const { return z_rotational_position_.get(); }

    inline void clear_y_rotational_position() { y_rotational_position_.clear(); }
    inline void set_y_rotational_position(const EmbeddedProto::uint32& value) { y_rotational_position_ = value; }
    inline void set_y_rotational_position(const EmbeddedProto::uint32&& value) { y_rotational_position_ = value; }
    inline EmbeddedProto::uint32& mutable_y_rotational_position() { return y_rotational_position_; }
    inline const EmbeddedProto::uint32& get_y_rotational_position() const { return y_rotational_position_; }
    inline EmbeddedProto::uint32::FIELD_TYPE y_rotational_position() const { return y_rotational_position_.get(); }

    inline void clear_pumpEnabled() { pumpEnabled_.clear(); }
    inline void set_pumpEnabled(const EmbeddedProto::boolean& value) { pumpEnabled_ = value; }
    inline void set_pumpEnabled(const EmbeddedProto::boolean&& value) { pumpEnabled_ = value; }
    inline EmbeddedProto::boolean& mutable_pumpEnabled() { return pumpEnabled_; }
    inline const EmbeddedProto::boolean& get_pumpEnabled() const { return pumpEnabled_; }
    inline EmbeddedProto::boolean::FIELD_TYPE pumpEnabled() const { return pumpEnabled_.get(); }

    inline void clear_valveClosed() { valveClosed_.clear(); }
    inline void set_valveClosed(const EmbeddedProto::boolean& value) { valveClosed_ = value; }
    inline void set_valveClosed(const EmbeddedProto::boolean&& value) { valveClosed_ = value; }
    inline EmbeddedProto::boolean& mutable_valveClosed() { return valveClosed_; }
    inline const EmbeddedProto::boolean& get_valveClosed() const { return valveClosed_; }
    inline EmbeddedProto::boolean::FIELD_TYPE valveClosed() const { return valveClosed_.get(); }

    inline void clear_pressureValue() { pressureValue_.clear(); }
    inline void set_pressureValue(const EmbeddedProto::uint32& value) { pressureValue_ = value; }
    inline void set_pressureValue(const EmbeddedProto::uint32&& value) { pressureValue_ = value; }
    inline EmbeddedProto::uint32& mutable_pressureValue() { return pressureValue_; }
    inline const EmbeddedProto::uint32& get_pressureValue() const { return pressureValue_; }
    inline EmbeddedProto::uint32::FIELD_TYPE pressureValue() const { return pressureValue_.get(); }


    ::EmbeddedProto::Error serialize(::EmbeddedProto::WriteBufferInterface& buffer) const override
    {
      ::EmbeddedProto::Error return_value = ::EmbeddedProto::Error::NO_ERRORS;

      if((0U != z_prismatic_position_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = z_prismatic_position_.serialize_with_id(static_cast<uint32_t>(id::Z_PRISMATIC_POSITION), buffer, false);
      }

      if((0U != z_rotational_position_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = z_rotational_position_.serialize_with_id(static_cast<uint32_t>(id::Z_ROTATIONAL_POSITION), buffer, false);
      }

      if((0U != y_rotational_position_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = y_rotational_position_.serialize_with_id(static_cast<uint32_t>(id::Y_ROTATIONAL_POSITION), buffer, false);
      }

      if((false != pumpEnabled_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = pumpEnabled_.serialize_with_id(static_cast<uint32_t>(id::PUMPENABLED), buffer, false);
      }

      if((false != valveClosed_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = valveClosed_.serialize_with_id(static_cast<uint32_t>(id::VALVECLOSED), buffer, false);
      }

      if((0U != pressureValue_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = pressureValue_.serialize_with_id(static_cast<uint32_t>(id::PRESSUREVALUE), buffer, false);
      }

      return return_value;
    };

    ::EmbeddedProto::Error deserialize(::EmbeddedProto::ReadBufferInterface& buffer) override
    {
      ::EmbeddedProto::Error return_value = ::EmbeddedProto::Error::NO_ERRORS;
      ::EmbeddedProto::WireFormatter::WireType wire_type = ::EmbeddedProto::WireFormatter::WireType::VARINT;
      uint32_t id_number = 0;
      id id_tag = id::NOT_SET;

      ::EmbeddedProto::Error tag_value = ::EmbeddedProto::WireFormatter::DeserializeTag(buffer, wire_type, id_number);
      while((::EmbeddedProto::Error::NO_ERRORS == return_value) && (::EmbeddedProto::Error::NO_ERRORS == tag_value))
      {
        id_tag = static_cast<id>(id_number);
        switch(id_tag)
        {
          case id::Z_PRISMATIC_POSITION:
            return_value = z_prismatic_position_.deserialize_check_type(buffer, wire_type);
            break;

          case id::Z_ROTATIONAL_POSITION:
            return_value = z_rotational_position_.deserialize_check_type(buffer, wire_type);
            break;

          case id::Y_ROTATIONAL_POSITION:
            return_value = y_rotational_position_.deserialize_check_type(buffer, wire_type);
            break;

          case id::PUMPENABLED:
            return_value = pumpEnabled_.deserialize_check_type(buffer, wire_type);
            break;

          case id::VALVECLOSED:
            return_value = valveClosed_.deserialize_check_type(buffer, wire_type);
            break;

          case id::PRESSUREVALUE:
            return_value = pressureValue_.deserialize_check_type(buffer, wire_type);
            break;

          case id::NOT_SET:
            return_value = ::EmbeddedProto::Error::INVALID_FIELD_ID;
            break;

          default:
            return_value = skip_unknown_field(buffer, wire_type);
            break;
        }

        if(::EmbeddedProto::Error::NO_ERRORS == return_value)
        {
          // Read the next tag.
          tag_value = ::EmbeddedProto::WireFormatter::DeserializeTag(buffer, wire_type, id_number);
        }
      }

      // When an error was detect while reading the tag but no other errors where found, set it in the return value.
      if((::EmbeddedProto::Error::NO_ERRORS == return_value)
         && (::EmbeddedProto::Error::NO_ERRORS != tag_value)
         && (::EmbeddedProto::Error::END_OF_BUFFER != tag_value)) // The end of the buffer is not an array in this case.
      {
        return_value = tag_value;
      }

      return return_value;
    };

    void clear() override
    {
      clear_z_prismatic_position();
      clear_z_rotational_position();
      clear_y_rotational_position();
      clear_pumpEnabled();
      clear_valveClosed();
      clear_pressureValue();

    }

    private:


      EmbeddedProto::uint32 z_prismatic_position_ = 0U;
      EmbeddedProto::uint32 z_rotational_position_ = 0U;
      EmbeddedProto::uint32 y_rotational_position_ = 0U;
      EmbeddedProto::boolean pumpEnabled_ = false;
      EmbeddedProto::boolean valveClosed_ = false;
      EmbeddedProto::uint32 pressureValue_ = 0U;

};

class HatStatus final: public ::EmbeddedProto::MessageInterface
{
  public:
    HatStatus() = default;
    HatStatus(const HatStatus& rhs )
    {
      set_hat_height(rhs.get_hat_height());
      set_pumpEnabled(rhs.get_pumpEnabled());
      set_valveClosed(rhs.get_valveClosed());
    }

    HatStatus(const HatStatus&& rhs ) noexcept
    {
      set_hat_height(rhs.get_hat_height());
      set_pumpEnabled(rhs.get_pumpEnabled());
      set_valveClosed(rhs.get_valveClosed());
    }

    ~HatStatus() override = default;

    enum class id : uint32_t
    {
      NOT_SET = 0,
      HAT_HEIGHT = 1,
      PUMPENABLED = 2,
      VALVECLOSED = 3
    };

    HatStatus& operator=(const HatStatus& rhs)
    {
      set_hat_height(rhs.get_hat_height());
      set_pumpEnabled(rhs.get_pumpEnabled());
      set_valveClosed(rhs.get_valveClosed());
      return *this;
    }

    HatStatus& operator=(const HatStatus&& rhs) noexcept
    {
      set_hat_height(rhs.get_hat_height());
      set_pumpEnabled(rhs.get_pumpEnabled());
      set_valveClosed(rhs.get_valveClosed());
      return *this;
    }

    inline void clear_hat_height() { hat_height_.clear(); }
    inline void set_hat_height(const EmbeddedProto::uint32& value) { hat_height_ = value; }
    inline void set_hat_height(const EmbeddedProto::uint32&& value) { hat_height_ = value; }
    inline EmbeddedProto::uint32& mutable_hat_height() { return hat_height_; }
    inline const EmbeddedProto::uint32& get_hat_height() const { return hat_height_; }
    inline EmbeddedProto::uint32::FIELD_TYPE hat_height() const { return hat_height_.get(); }

    inline void clear_pumpEnabled() { pumpEnabled_.clear(); }
    inline void set_pumpEnabled(const EmbeddedProto::boolean& value) { pumpEnabled_ = value; }
    inline void set_pumpEnabled(const EmbeddedProto::boolean&& value) { pumpEnabled_ = value; }
    inline EmbeddedProto::boolean& mutable_pumpEnabled() { return pumpEnabled_; }
    inline const EmbeddedProto::boolean& get_pumpEnabled() const { return pumpEnabled_; }
    inline EmbeddedProto::boolean::FIELD_TYPE pumpEnabled() const { return pumpEnabled_.get(); }

    inline void clear_valveClosed() { valveClosed_.clear(); }
    inline void set_valveClosed(const EmbeddedProto::boolean& value) { valveClosed_ = value; }
    inline void set_valveClosed(const EmbeddedProto::boolean&& value) { valveClosed_ = value; }
    inline EmbeddedProto::boolean& mutable_valveClosed() { return valveClosed_; }
    inline const EmbeddedProto::boolean& get_valveClosed() const { return valveClosed_; }
    inline EmbeddedProto::boolean::FIELD_TYPE valveClosed() const { return valveClosed_.get(); }


    ::EmbeddedProto::Error serialize(::EmbeddedProto::WriteBufferInterface& buffer) const override
    {
      ::EmbeddedProto::Error return_value = ::EmbeddedProto::Error::NO_ERRORS;

      if((0U != hat_height_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = hat_height_.serialize_with_id(static_cast<uint32_t>(id::HAT_HEIGHT), buffer, false);
      }

      if((false != pumpEnabled_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = pumpEnabled_.serialize_with_id(static_cast<uint32_t>(id::PUMPENABLED), buffer, false);
      }

      if((false != valveClosed_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = valveClosed_.serialize_with_id(static_cast<uint32_t>(id::VALVECLOSED), buffer, false);
      }

      return return_value;
    };

    ::EmbeddedProto::Error deserialize(::EmbeddedProto::ReadBufferInterface& buffer) override
    {
      ::EmbeddedProto::Error return_value = ::EmbeddedProto::Error::NO_ERRORS;
      ::EmbeddedProto::WireFormatter::WireType wire_type = ::EmbeddedProto::WireFormatter::WireType::VARINT;
      uint32_t id_number = 0;
      id id_tag = id::NOT_SET;

      ::EmbeddedProto::Error tag_value = ::EmbeddedProto::WireFormatter::DeserializeTag(buffer, wire_type, id_number);
      while((::EmbeddedProto::Error::NO_ERRORS == return_value) && (::EmbeddedProto::Error::NO_ERRORS == tag_value))
      {
        id_tag = static_cast<id>(id_number);
        switch(id_tag)
        {
          case id::HAT_HEIGHT:
            return_value = hat_height_.deserialize_check_type(buffer, wire_type);
            break;

          case id::PUMPENABLED:
            return_value = pumpEnabled_.deserialize_check_type(buffer, wire_type);
            break;

          case id::VALVECLOSED:
            return_value = valveClosed_.deserialize_check_type(buffer, wire_type);
            break;

          case id::NOT_SET:
            return_value = ::EmbeddedProto::Error::INVALID_FIELD_ID;
            break;

          default:
            return_value = skip_unknown_field(buffer, wire_type);
            break;
        }

        if(::EmbeddedProto::Error::NO_ERRORS == return_value)
        {
          // Read the next tag.
          tag_value = ::EmbeddedProto::WireFormatter::DeserializeTag(buffer, wire_type, id_number);
        }
      }

      // When an error was detect while reading the tag but no other errors where found, set it in the return value.
      if((::EmbeddedProto::Error::NO_ERRORS == return_value)
         && (::EmbeddedProto::Error::NO_ERRORS != tag_value)
         && (::EmbeddedProto::Error::END_OF_BUFFER != tag_value)) // The end of the buffer is not an array in this case.
      {
        return_value = tag_value;
      }

      return return_value;
    };

    void clear() override
    {
      clear_hat_height();
      clear_pumpEnabled();
      clear_valveClosed();

    }

    private:


      EmbeddedProto::uint32 hat_height_ = 0U;
      EmbeddedProto::boolean pumpEnabled_ = false;
      EmbeddedProto::boolean valveClosed_ = false;

};

class ProcedureStatus final: public ::EmbeddedProto::MessageInterface
{
  public:
    ProcedureStatus() = default;
    ProcedureStatus(const ProcedureStatus& rhs )
    {
      set_status(rhs.get_status());
    }

    ProcedureStatus(const ProcedureStatus&& rhs ) noexcept
    {
      set_status(rhs.get_status());
    }

    ~ProcedureStatus() override = default;

    enum class Status : uint32_t
    {
      SUCCESS = 0,
      RUNNING = 1,
      FAILURE = 2,
      POSITION_UNREACHABLE = 3,
      UNABLE_VACUUM = 4
    };

    enum class id : uint32_t
    {
      NOT_SET = 0,
      STATUS = 1
    };

    ProcedureStatus& operator=(const ProcedureStatus& rhs)
    {
      set_status(rhs.get_status());
      return *this;
    }

    ProcedureStatus& operator=(const ProcedureStatus&& rhs) noexcept
    {
      set_status(rhs.get_status());
      return *this;
    }

    inline void clear_status() { status_ = static_cast<Status>(0); }
    inline void set_status(const Status& value) { status_ = value; }
    inline void set_status(const Status&& value) { status_ = value; }
    inline const Status& get_status() const { return status_; }
    inline Status status() const { return status_; }


    ::EmbeddedProto::Error serialize(::EmbeddedProto::WriteBufferInterface& buffer) const override
    {
      ::EmbeddedProto::Error return_value = ::EmbeddedProto::Error::NO_ERRORS;

      if((static_cast<Status>(0) != status_) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        EmbeddedProto::uint32 value = 0;
        value.set(static_cast<uint32_t>(status_));
        return_value = value.serialize_with_id(static_cast<uint32_t>(id::STATUS), buffer, false);
      }

      return return_value;
    };

    ::EmbeddedProto::Error deserialize(::EmbeddedProto::ReadBufferInterface& buffer) override
    {
      ::EmbeddedProto::Error return_value = ::EmbeddedProto::Error::NO_ERRORS;
      ::EmbeddedProto::WireFormatter::WireType wire_type = ::EmbeddedProto::WireFormatter::WireType::VARINT;
      uint32_t id_number = 0;
      id id_tag = id::NOT_SET;

      ::EmbeddedProto::Error tag_value = ::EmbeddedProto::WireFormatter::DeserializeTag(buffer, wire_type, id_number);
      while((::EmbeddedProto::Error::NO_ERRORS == return_value) && (::EmbeddedProto::Error::NO_ERRORS == tag_value))
      {
        id_tag = static_cast<id>(id_number);
        switch(id_tag)
        {
          case id::STATUS:
            if(::EmbeddedProto::WireFormatter::WireType::VARINT == wire_type)
            {
              uint32_t value = 0;
              return_value = ::EmbeddedProto::WireFormatter::DeserializeVarint(buffer, value);
              if(::EmbeddedProto::Error::NO_ERRORS == return_value)
              {
                set_status(static_cast<Status>(value));
              }
            }
            else
            {
              // Wire type does not match field.
              return_value = ::EmbeddedProto::Error::INVALID_WIRETYPE;
            }
            break;

          case id::NOT_SET:
            return_value = ::EmbeddedProto::Error::INVALID_FIELD_ID;
            break;

          default:
            return_value = skip_unknown_field(buffer, wire_type);
            break;
        }

        if(::EmbeddedProto::Error::NO_ERRORS == return_value)
        {
          // Read the next tag.
          tag_value = ::EmbeddedProto::WireFormatter::DeserializeTag(buffer, wire_type, id_number);
        }
      }

      // When an error was detect while reading the tag but no other errors where found, set it in the return value.
      if((::EmbeddedProto::Error::NO_ERRORS == return_value)
         && (::EmbeddedProto::Error::NO_ERRORS != tag_value)
         && (::EmbeddedProto::Error::END_OF_BUFFER != tag_value)) // The end of the buffer is not an array in this case.
      {
        return_value = tag_value;
      }

      return return_value;
    };

    void clear() override
    {
      clear_status();

    }

    private:


      Status status_ = static_cast<Status>(0);

};

class IOAnswer final: public ::EmbeddedProto::MessageInterface
{
  public:
    IOAnswer() = default;
    IOAnswer(const IOAnswer& rhs )
    {
      if(rhs.get_which_inner() != which_inner_)
      {
        // First delete the old object in the oneof.
        clear_inner();
      }

      switch(rhs.get_which_inner())
      {
        case id::ARM_STATUS:
          set_arm_status(rhs.get_arm_status());
          break;

        case id::HAT_STATUS:
          set_hat_status(rhs.get_hat_status());
          break;

        case id::PROCEDURE_STATUS:
          set_procedure_status(rhs.get_procedure_status());
          break;

        default:
          break;
      }

    }

    IOAnswer(const IOAnswer&& rhs ) noexcept
    {
      if(rhs.get_which_inner() != which_inner_)
      {
        // First delete the old object in the oneof.
        clear_inner();
      }

      switch(rhs.get_which_inner())
      {
        case id::ARM_STATUS:
          set_arm_status(rhs.get_arm_status());
          break;

        case id::HAT_STATUS:
          set_hat_status(rhs.get_hat_status());
          break;

        case id::PROCEDURE_STATUS:
          set_procedure_status(rhs.get_procedure_status());
          break;

        default:
          break;
      }

    }

    ~IOAnswer() override = default;

    enum class id : uint32_t
    {
      NOT_SET = 0,
      ARM_STATUS = 1,
      HAT_STATUS = 2,
      PROCEDURE_STATUS = 3
    };

    IOAnswer& operator=(const IOAnswer& rhs)
    {
      if(rhs.get_which_inner() != which_inner_)
      {
        // First delete the old object in the oneof.
        clear_inner();
      }

      switch(rhs.get_which_inner())
      {
        case id::ARM_STATUS:
          set_arm_status(rhs.get_arm_status());
          break;

        case id::HAT_STATUS:
          set_hat_status(rhs.get_hat_status());
          break;

        case id::PROCEDURE_STATUS:
          set_procedure_status(rhs.get_procedure_status());
          break;

        default:
          break;
      }

      return *this;
    }

    IOAnswer& operator=(const IOAnswer&& rhs) noexcept
    {
      if(rhs.get_which_inner() != which_inner_)
      {
        // First delete the old object in the oneof.
        clear_inner();
      }

      switch(rhs.get_which_inner())
      {
        case id::ARM_STATUS:
          set_arm_status(rhs.get_arm_status());
          break;

        case id::HAT_STATUS:
          set_hat_status(rhs.get_hat_status());
          break;

        case id::PROCEDURE_STATUS:
          set_procedure_status(rhs.get_procedure_status());
          break;

        default:
          break;
      }

      return *this;
    }

    id get_which_inner() const { return which_inner_; }

    inline bool has_arm_status() const
    {
      return id::ARM_STATUS == which_inner_;
    }
    inline void clear_arm_status()
    {
      if(id::ARM_STATUS == which_inner_)
      {
        which_inner_ = id::NOT_SET;
        inner_.arm_status_.~ArmStatus();
      }
    }
    inline void set_arm_status(const ArmStatus& value)
    {
      if(id::ARM_STATUS != which_inner_)
      {
        init_inner(id::ARM_STATUS);
      }
      inner_.arm_status_ = value;
    }
    inline void set_arm_status(const ArmStatus&& value)
    {
      if(id::ARM_STATUS != which_inner_)
      {
        init_inner(id::ARM_STATUS);
      }
      inner_.arm_status_ = value;
    }
    inline ArmStatus& mutable_arm_status()
    {
      if(id::ARM_STATUS != which_inner_)
      {
        init_inner(id::ARM_STATUS);
      }
      return inner_.arm_status_;
    }
    inline const ArmStatus& get_arm_status() const { return inner_.arm_status_; }
    inline const ArmStatus& arm_status() const { return inner_.arm_status_; }

    inline bool has_hat_status() const
    {
      return id::HAT_STATUS == which_inner_;
    }
    inline void clear_hat_status()
    {
      if(id::HAT_STATUS == which_inner_)
      {
        which_inner_ = id::NOT_SET;
        inner_.hat_status_.~HatStatus();
      }
    }
    inline void set_hat_status(const HatStatus& value)
    {
      if(id::HAT_STATUS != which_inner_)
      {
        init_inner(id::HAT_STATUS);
      }
      inner_.hat_status_ = value;
    }
    inline void set_hat_status(const HatStatus&& value)
    {
      if(id::HAT_STATUS != which_inner_)
      {
        init_inner(id::HAT_STATUS);
      }
      inner_.hat_status_ = value;
    }
    inline HatStatus& mutable_hat_status()
    {
      if(id::HAT_STATUS != which_inner_)
      {
        init_inner(id::HAT_STATUS);
      }
      return inner_.hat_status_;
    }
    inline const HatStatus& get_hat_status() const { return inner_.hat_status_; }
    inline const HatStatus& hat_status() const { return inner_.hat_status_; }

    inline bool has_procedure_status() const
    {
      return id::PROCEDURE_STATUS == which_inner_;
    }
    inline void clear_procedure_status()
    {
      if(id::PROCEDURE_STATUS == which_inner_)
      {
        which_inner_ = id::NOT_SET;
        inner_.procedure_status_.~ProcedureStatus();
      }
    }
    inline void set_procedure_status(const ProcedureStatus& value)
    {
      if(id::PROCEDURE_STATUS != which_inner_)
      {
        init_inner(id::PROCEDURE_STATUS);
      }
      inner_.procedure_status_ = value;
    }
    inline void set_procedure_status(const ProcedureStatus&& value)
    {
      if(id::PROCEDURE_STATUS != which_inner_)
      {
        init_inner(id::PROCEDURE_STATUS);
      }
      inner_.procedure_status_ = value;
    }
    inline ProcedureStatus& mutable_procedure_status()
    {
      if(id::PROCEDURE_STATUS != which_inner_)
      {
        init_inner(id::PROCEDURE_STATUS);
      }
      return inner_.procedure_status_;
    }
    inline const ProcedureStatus& get_procedure_status() const { return inner_.procedure_status_; }
    inline const ProcedureStatus& procedure_status() const { return inner_.procedure_status_; }


    ::EmbeddedProto::Error serialize(::EmbeddedProto::WriteBufferInterface& buffer) const override
    {
      ::EmbeddedProto::Error return_value = ::EmbeddedProto::Error::NO_ERRORS;

      switch(which_inner_)
      {
        case id::ARM_STATUS:
          if(has_arm_status() && (::EmbeddedProto::Error::NO_ERRORS == return_value))
          {
            return_value = inner_.arm_status_.serialize_with_id(static_cast<uint32_t>(id::ARM_STATUS), buffer, true);
          }
          break;

        case id::HAT_STATUS:
          if(has_hat_status() && (::EmbeddedProto::Error::NO_ERRORS == return_value))
          {
            return_value = inner_.hat_status_.serialize_with_id(static_cast<uint32_t>(id::HAT_STATUS), buffer, true);
          }
          break;

        case id::PROCEDURE_STATUS:
          if(has_procedure_status() && (::EmbeddedProto::Error::NO_ERRORS == return_value))
          {
            return_value = inner_.procedure_status_.serialize_with_id(static_cast<uint32_t>(id::PROCEDURE_STATUS), buffer, true);
          }
          break;

        default:
          break;
      }

      return return_value;
    };

    ::EmbeddedProto::Error deserialize(::EmbeddedProto::ReadBufferInterface& buffer) override
    {
      ::EmbeddedProto::Error return_value = ::EmbeddedProto::Error::NO_ERRORS;
      ::EmbeddedProto::WireFormatter::WireType wire_type = ::EmbeddedProto::WireFormatter::WireType::VARINT;
      uint32_t id_number = 0;
      id id_tag = id::NOT_SET;

      ::EmbeddedProto::Error tag_value = ::EmbeddedProto::WireFormatter::DeserializeTag(buffer, wire_type, id_number);
      while((::EmbeddedProto::Error::NO_ERRORS == return_value) && (::EmbeddedProto::Error::NO_ERRORS == tag_value))
      {
        id_tag = static_cast<id>(id_number);
        switch(id_tag)
        {
          case id::ARM_STATUS:
            return_value = deserialize_inner(id::ARM_STATUS, inner_.arm_status_, buffer, wire_type);

            break;

          case id::HAT_STATUS:
            return_value = deserialize_inner(id::HAT_STATUS, inner_.hat_status_, buffer, wire_type);

            break;

          case id::PROCEDURE_STATUS:
            return_value = deserialize_inner(id::PROCEDURE_STATUS, inner_.procedure_status_, buffer, wire_type);

            break;

          case id::NOT_SET:
            return_value = ::EmbeddedProto::Error::INVALID_FIELD_ID;
            break;

          default:
            return_value = skip_unknown_field(buffer, wire_type);
            break;
        }

        if(::EmbeddedProto::Error::NO_ERRORS == return_value)
        {
          // Read the next tag.
          tag_value = ::EmbeddedProto::WireFormatter::DeserializeTag(buffer, wire_type, id_number);
        }
      }

      // When an error was detect while reading the tag but no other errors where found, set it in the return value.
      if((::EmbeddedProto::Error::NO_ERRORS == return_value)
         && (::EmbeddedProto::Error::NO_ERRORS != tag_value)
         && (::EmbeddedProto::Error::END_OF_BUFFER != tag_value)) // The end of the buffer is not an array in this case.
      {
        return_value = tag_value;
      }

      return return_value;
    };

    void clear() override
    {
      clear_inner();

    }

    private:



      id which_inner_ = id::NOT_SET;
      union inner
      {
        inner() {}
        ~inner() {}
        ArmStatus arm_status_;
        HatStatus hat_status_;
        ProcedureStatus procedure_status_;
      };
      inner inner_;

      void init_inner(const id field_id)
      {
        if(id::NOT_SET != which_inner_)
        {
          // First delete the old object in the oneof.
          clear_inner();
        }

        // C++11 unions only support nontrivial members when you explicitly call the placement new statement.
        switch(field_id)
        {
          case id::ARM_STATUS:
            new(&inner_.arm_status_) ArmStatus;
            which_inner_ = id::ARM_STATUS;
            break;

          case id::HAT_STATUS:
            new(&inner_.hat_status_) HatStatus;
            which_inner_ = id::HAT_STATUS;
            break;

          case id::PROCEDURE_STATUS:
            new(&inner_.procedure_status_) ProcedureStatus;
            which_inner_ = id::PROCEDURE_STATUS;
            break;

          default:
            break;
         }

         which_inner_ = field_id;
      }

      void clear_inner()
      {
        switch(which_inner_)
        {
          case id::ARM_STATUS:
            inner_.arm_status_.~ArmStatus(); // NOSONAR Unions require this.
            break;
          case id::HAT_STATUS:
            inner_.hat_status_.~HatStatus(); // NOSONAR Unions require this.
            break;
          case id::PROCEDURE_STATUS:
            inner_.procedure_status_.~ProcedureStatus(); // NOSONAR Unions require this.
            break;
          default:
            break;
        }
        which_inner_ = id::NOT_SET;
      }

      ::EmbeddedProto::Error deserialize_inner(const id field_id, ::EmbeddedProto::Field& field,
                                    ::EmbeddedProto::ReadBufferInterface& buffer,
                                    const ::EmbeddedProto::WireFormatter::WireType wire_type)
      {
        if(field_id != which_inner_)
        {
          init_inner(field_id);
        }
        ::EmbeddedProto::Error return_value = field.deserialize_check_type(buffer, wire_type);
        if(::EmbeddedProto::Error::NO_ERRORS != return_value)
        {
          clear_inner();
        }
        return return_value;
      }

};

#endif // IOBOARDCOMMUNICATIONUP_H