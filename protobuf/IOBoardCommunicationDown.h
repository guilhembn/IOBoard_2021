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
#ifndef IOBOARDCOMMUNICATIONDOWN_H
#define IOBOARDCOMMUNICATIONDOWN_H

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


enum class IORequest : uint32_t
{
  ARM_STATUS = 0,
  HAT_STATUS = 1
};

class SequenceCommand final: public ::EmbeddedProto::MessageInterface
{
  public:
    SequenceCommand() = default;
    SequenceCommand(const SequenceCommand& rhs )
    {
      set_sequence(rhs.get_sequence());
      set_param(rhs.get_param());
    }

    SequenceCommand(const SequenceCommand&& rhs ) noexcept
    {
      set_sequence(rhs.get_sequence());
      set_param(rhs.get_param());
    }

    ~SequenceCommand() override = default;

    enum class Sequence : uint32_t
    {
      HOME = 0,
      PUT_ON_STACK = 1,
      TURN_AND_PUT_ON_STACK = 2,
      TAKE_FROM_STACK = 3
    };

    enum class id : uint32_t
    {
      NOT_SET = 0,
      SEQUENCE = 1,
      PARAM = 2
    };

    SequenceCommand& operator=(const SequenceCommand& rhs)
    {
      set_sequence(rhs.get_sequence());
      set_param(rhs.get_param());
      return *this;
    }

    SequenceCommand& operator=(const SequenceCommand&& rhs) noexcept
    {
      set_sequence(rhs.get_sequence());
      set_param(rhs.get_param());
      return *this;
    }

    inline void clear_sequence() { sequence_ = static_cast<Sequence>(0); }
    inline void set_sequence(const Sequence& value) { sequence_ = value; }
    inline void set_sequence(const Sequence&& value) { sequence_ = value; }
    inline const Sequence& get_sequence() const { return sequence_; }
    inline Sequence sequence() const { return sequence_; }

    inline void clear_param() { param_.clear(); }
    inline void set_param(const EmbeddedProto::uint32& value) { param_ = value; }
    inline void set_param(const EmbeddedProto::uint32&& value) { param_ = value; }
    inline EmbeddedProto::uint32& mutable_param() { return param_; }
    inline const EmbeddedProto::uint32& get_param() const { return param_; }
    inline EmbeddedProto::uint32::FIELD_TYPE param() const { return param_.get(); }


    ::EmbeddedProto::Error serialize(::EmbeddedProto::WriteBufferInterface& buffer) const override
    {
      ::EmbeddedProto::Error return_value = ::EmbeddedProto::Error::NO_ERRORS;

      if((static_cast<Sequence>(0) != sequence_) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        EmbeddedProto::uint32 value = 0;
        value.set(static_cast<uint32_t>(sequence_));
        return_value = value.serialize_with_id(static_cast<uint32_t>(id::SEQUENCE), buffer, false);
      }

      if((0U != param_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = param_.serialize_with_id(static_cast<uint32_t>(id::PARAM), buffer, false);
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
          case id::SEQUENCE:
            if(::EmbeddedProto::WireFormatter::WireType::VARINT == wire_type)
            {
              uint32_t value = 0;
              return_value = ::EmbeddedProto::WireFormatter::DeserializeVarint(buffer, value);
              if(::EmbeddedProto::Error::NO_ERRORS == return_value)
              {
                set_sequence(static_cast<Sequence>(value));
              }
            }
            else
            {
              // Wire type does not match field.
              return_value = ::EmbeddedProto::Error::INVALID_WIRETYPE;
            }
            break;

          case id::PARAM:
            return_value = param_.deserialize_check_type(buffer, wire_type);
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
      clear_sequence();
      clear_param();

    }

    private:


      Sequence sequence_ = static_cast<Sequence>(0);
      EmbeddedProto::uint32 param_ = 0U;

};

class ArmPositionCommand final: public ::EmbeddedProto::MessageInterface
{
  public:
    ArmPositionCommand() = default;
    ArmPositionCommand(const ArmPositionCommand& rhs )
    {
      set_z_prismatic_position(rhs.get_z_prismatic_position());
      set_z_rotational_position(rhs.get_z_rotational_position());
      set_y_rotational_position(rhs.get_y_rotational_position());
    }

    ArmPositionCommand(const ArmPositionCommand&& rhs ) noexcept
    {
      set_z_prismatic_position(rhs.get_z_prismatic_position());
      set_z_rotational_position(rhs.get_z_rotational_position());
      set_y_rotational_position(rhs.get_y_rotational_position());
    }

    ~ArmPositionCommand() override = default;

    enum class id : uint32_t
    {
      NOT_SET = 0,
      Z_PRISMATIC_POSITION = 1,
      Z_ROTATIONAL_POSITION = 2,
      Y_ROTATIONAL_POSITION = 3
    };

    ArmPositionCommand& operator=(const ArmPositionCommand& rhs)
    {
      set_z_prismatic_position(rhs.get_z_prismatic_position());
      set_z_rotational_position(rhs.get_z_rotational_position());
      set_y_rotational_position(rhs.get_y_rotational_position());
      return *this;
    }

    ArmPositionCommand& operator=(const ArmPositionCommand&& rhs) noexcept
    {
      set_z_prismatic_position(rhs.get_z_prismatic_position());
      set_z_rotational_position(rhs.get_z_rotational_position());
      set_y_rotational_position(rhs.get_y_rotational_position());
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

    }

    private:


      EmbeddedProto::uint32 z_prismatic_position_ = 0U;
      EmbeddedProto::uint32 z_rotational_position_ = 0U;
      EmbeddedProto::uint32 y_rotational_position_ = 0U;

};

class ArmPumpCommand final: public ::EmbeddedProto::MessageInterface
{
  public:
    ArmPumpCommand() = default;
    ArmPumpCommand(const ArmPumpCommand& rhs )
    {
      set_enable(rhs.get_enable());
    }

    ArmPumpCommand(const ArmPumpCommand&& rhs ) noexcept
    {
      set_enable(rhs.get_enable());
    }

    ~ArmPumpCommand() override = default;

    enum class id : uint32_t
    {
      NOT_SET = 0,
      ENABLE = 1
    };

    ArmPumpCommand& operator=(const ArmPumpCommand& rhs)
    {
      set_enable(rhs.get_enable());
      return *this;
    }

    ArmPumpCommand& operator=(const ArmPumpCommand&& rhs) noexcept
    {
      set_enable(rhs.get_enable());
      return *this;
    }

    inline void clear_enable() { enable_.clear(); }
    inline void set_enable(const EmbeddedProto::boolean& value) { enable_ = value; }
    inline void set_enable(const EmbeddedProto::boolean&& value) { enable_ = value; }
    inline EmbeddedProto::boolean& mutable_enable() { return enable_; }
    inline const EmbeddedProto::boolean& get_enable() const { return enable_; }
    inline EmbeddedProto::boolean::FIELD_TYPE enable() const { return enable_.get(); }


    ::EmbeddedProto::Error serialize(::EmbeddedProto::WriteBufferInterface& buffer) const override
    {
      ::EmbeddedProto::Error return_value = ::EmbeddedProto::Error::NO_ERRORS;

      if((false != enable_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = enable_.serialize_with_id(static_cast<uint32_t>(id::ENABLE), buffer, false);
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
          case id::ENABLE:
            return_value = enable_.deserialize_check_type(buffer, wire_type);
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
      clear_enable();

    }

    private:


      EmbeddedProto::boolean enable_ = false;

};

class HatPositionCommand final: public ::EmbeddedProto::MessageInterface
{
  public:
    HatPositionCommand() = default;
    HatPositionCommand(const HatPositionCommand& rhs )
    {
      set_hat_height(rhs.get_hat_height());
    }

    HatPositionCommand(const HatPositionCommand&& rhs ) noexcept
    {
      set_hat_height(rhs.get_hat_height());
    }

    ~HatPositionCommand() override = default;

    enum class id : uint32_t
    {
      NOT_SET = 0,
      HAT_HEIGHT = 1
    };

    HatPositionCommand& operator=(const HatPositionCommand& rhs)
    {
      set_hat_height(rhs.get_hat_height());
      return *this;
    }

    HatPositionCommand& operator=(const HatPositionCommand&& rhs) noexcept
    {
      set_hat_height(rhs.get_hat_height());
      return *this;
    }

    inline void clear_hat_height() { hat_height_.clear(); }
    inline void set_hat_height(const EmbeddedProto::uint32& value) { hat_height_ = value; }
    inline void set_hat_height(const EmbeddedProto::uint32&& value) { hat_height_ = value; }
    inline EmbeddedProto::uint32& mutable_hat_height() { return hat_height_; }
    inline const EmbeddedProto::uint32& get_hat_height() const { return hat_height_; }
    inline EmbeddedProto::uint32::FIELD_TYPE hat_height() const { return hat_height_.get(); }


    ::EmbeddedProto::Error serialize(::EmbeddedProto::WriteBufferInterface& buffer) const override
    {
      ::EmbeddedProto::Error return_value = ::EmbeddedProto::Error::NO_ERRORS;

      if((0U != hat_height_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = hat_height_.serialize_with_id(static_cast<uint32_t>(id::HAT_HEIGHT), buffer, false);
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

    }

    private:


      EmbeddedProto::uint32 hat_height_ = 0U;

};

class HatPumpCommand final: public ::EmbeddedProto::MessageInterface
{
  public:
    HatPumpCommand() = default;
    HatPumpCommand(const HatPumpCommand& rhs )
    {
      set_enable(rhs.get_enable());
    }

    HatPumpCommand(const HatPumpCommand&& rhs ) noexcept
    {
      set_enable(rhs.get_enable());
    }

    ~HatPumpCommand() override = default;

    enum class id : uint32_t
    {
      NOT_SET = 0,
      ENABLE = 1
    };

    HatPumpCommand& operator=(const HatPumpCommand& rhs)
    {
      set_enable(rhs.get_enable());
      return *this;
    }

    HatPumpCommand& operator=(const HatPumpCommand&& rhs) noexcept
    {
      set_enable(rhs.get_enable());
      return *this;
    }

    inline void clear_enable() { enable_.clear(); }
    inline void set_enable(const EmbeddedProto::boolean& value) { enable_ = value; }
    inline void set_enable(const EmbeddedProto::boolean&& value) { enable_ = value; }
    inline EmbeddedProto::boolean& mutable_enable() { return enable_; }
    inline const EmbeddedProto::boolean& get_enable() const { return enable_; }
    inline EmbeddedProto::boolean::FIELD_TYPE enable() const { return enable_.get(); }


    ::EmbeddedProto::Error serialize(::EmbeddedProto::WriteBufferInterface& buffer) const override
    {
      ::EmbeddedProto::Error return_value = ::EmbeddedProto::Error::NO_ERRORS;

      if((false != enable_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = enable_.serialize_with_id(static_cast<uint32_t>(id::ENABLE), buffer, false);
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
          case id::ENABLE:
            return_value = enable_.deserialize_check_type(buffer, wire_type);
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
      clear_enable();

    }

    private:


      EmbeddedProto::boolean enable_ = false;

};

class IOCommand final: public ::EmbeddedProto::MessageInterface
{
  public:
    IOCommand() = default;
    IOCommand(const IOCommand& rhs )
    {
      if(rhs.get_which_inner() != which_inner_)
      {
        // First delete the old object in the oneof.
        clear_inner();
      }

      switch(rhs.get_which_inner())
      {
        case id::SEQUENCE_COMMAND:
          set_sequence_command(rhs.get_sequence_command());
          break;

        case id::ARM_POSITION_COMMAND:
          set_arm_position_command(rhs.get_arm_position_command());
          break;

        case id::ARM_PUMP_COMMAND:
          set_arm_pump_command(rhs.get_arm_pump_command());
          break;

        case id::HAT_POSITION_COMMAND:
          set_hat_position_command(rhs.get_hat_position_command());
          break;

        case id::HAT_PUMP_COMMAND:
          set_hat_pump_command(rhs.get_hat_pump_command());
          break;

        case id::IO_REQUEST:
          set_io_request(rhs.get_io_request());
          break;

        default:
          break;
      }

    }

    IOCommand(const IOCommand&& rhs ) noexcept
    {
      if(rhs.get_which_inner() != which_inner_)
      {
        // First delete the old object in the oneof.
        clear_inner();
      }

      switch(rhs.get_which_inner())
      {
        case id::SEQUENCE_COMMAND:
          set_sequence_command(rhs.get_sequence_command());
          break;

        case id::ARM_POSITION_COMMAND:
          set_arm_position_command(rhs.get_arm_position_command());
          break;

        case id::ARM_PUMP_COMMAND:
          set_arm_pump_command(rhs.get_arm_pump_command());
          break;

        case id::HAT_POSITION_COMMAND:
          set_hat_position_command(rhs.get_hat_position_command());
          break;

        case id::HAT_PUMP_COMMAND:
          set_hat_pump_command(rhs.get_hat_pump_command());
          break;

        case id::IO_REQUEST:
          set_io_request(rhs.get_io_request());
          break;

        default:
          break;
      }

    }

    ~IOCommand() override = default;

    enum class id : uint32_t
    {
      NOT_SET = 0,
      SEQUENCE_COMMAND = 1,
      ARM_POSITION_COMMAND = 2,
      ARM_PUMP_COMMAND = 3,
      HAT_POSITION_COMMAND = 4,
      HAT_PUMP_COMMAND = 5,
      IO_REQUEST = 6
    };

    IOCommand& operator=(const IOCommand& rhs)
    {
      if(rhs.get_which_inner() != which_inner_)
      {
        // First delete the old object in the oneof.
        clear_inner();
      }

      switch(rhs.get_which_inner())
      {
        case id::SEQUENCE_COMMAND:
          set_sequence_command(rhs.get_sequence_command());
          break;

        case id::ARM_POSITION_COMMAND:
          set_arm_position_command(rhs.get_arm_position_command());
          break;

        case id::ARM_PUMP_COMMAND:
          set_arm_pump_command(rhs.get_arm_pump_command());
          break;

        case id::HAT_POSITION_COMMAND:
          set_hat_position_command(rhs.get_hat_position_command());
          break;

        case id::HAT_PUMP_COMMAND:
          set_hat_pump_command(rhs.get_hat_pump_command());
          break;

        case id::IO_REQUEST:
          set_io_request(rhs.get_io_request());
          break;

        default:
          break;
      }

      return *this;
    }

    IOCommand& operator=(const IOCommand&& rhs) noexcept
    {
      if(rhs.get_which_inner() != which_inner_)
      {
        // First delete the old object in the oneof.
        clear_inner();
      }

      switch(rhs.get_which_inner())
      {
        case id::SEQUENCE_COMMAND:
          set_sequence_command(rhs.get_sequence_command());
          break;

        case id::ARM_POSITION_COMMAND:
          set_arm_position_command(rhs.get_arm_position_command());
          break;

        case id::ARM_PUMP_COMMAND:
          set_arm_pump_command(rhs.get_arm_pump_command());
          break;

        case id::HAT_POSITION_COMMAND:
          set_hat_position_command(rhs.get_hat_position_command());
          break;

        case id::HAT_PUMP_COMMAND:
          set_hat_pump_command(rhs.get_hat_pump_command());
          break;

        case id::IO_REQUEST:
          set_io_request(rhs.get_io_request());
          break;

        default:
          break;
      }

      return *this;
    }

    id get_which_inner() const { return which_inner_; }

    inline bool has_sequence_command() const
    {
      return id::SEQUENCE_COMMAND == which_inner_;
    }
    inline void clear_sequence_command()
    {
      if(id::SEQUENCE_COMMAND == which_inner_)
      {
        which_inner_ = id::NOT_SET;
        inner_.sequence_command_.~SequenceCommand();
      }
    }
    inline void set_sequence_command(const SequenceCommand& value)
    {
      if(id::SEQUENCE_COMMAND != which_inner_)
      {
        init_inner(id::SEQUENCE_COMMAND);
      }
      inner_.sequence_command_ = value;
    }
    inline void set_sequence_command(const SequenceCommand&& value)
    {
      if(id::SEQUENCE_COMMAND != which_inner_)
      {
        init_inner(id::SEQUENCE_COMMAND);
      }
      inner_.sequence_command_ = value;
    }
    inline SequenceCommand& mutable_sequence_command()
    {
      if(id::SEQUENCE_COMMAND != which_inner_)
      {
        init_inner(id::SEQUENCE_COMMAND);
      }
      return inner_.sequence_command_;
    }
    inline const SequenceCommand& get_sequence_command() const { return inner_.sequence_command_; }
    inline const SequenceCommand& sequence_command() const { return inner_.sequence_command_; }

    inline bool has_arm_position_command() const
    {
      return id::ARM_POSITION_COMMAND == which_inner_;
    }
    inline void clear_arm_position_command()
    {
      if(id::ARM_POSITION_COMMAND == which_inner_)
      {
        which_inner_ = id::NOT_SET;
        inner_.arm_position_command_.~ArmPositionCommand();
      }
    }
    inline void set_arm_position_command(const ArmPositionCommand& value)
    {
      if(id::ARM_POSITION_COMMAND != which_inner_)
      {
        init_inner(id::ARM_POSITION_COMMAND);
      }
      inner_.arm_position_command_ = value;
    }
    inline void set_arm_position_command(const ArmPositionCommand&& value)
    {
      if(id::ARM_POSITION_COMMAND != which_inner_)
      {
        init_inner(id::ARM_POSITION_COMMAND);
      }
      inner_.arm_position_command_ = value;
    }
    inline ArmPositionCommand& mutable_arm_position_command()
    {
      if(id::ARM_POSITION_COMMAND != which_inner_)
      {
        init_inner(id::ARM_POSITION_COMMAND);
      }
      return inner_.arm_position_command_;
    }
    inline const ArmPositionCommand& get_arm_position_command() const { return inner_.arm_position_command_; }
    inline const ArmPositionCommand& arm_position_command() const { return inner_.arm_position_command_; }

    inline bool has_arm_pump_command() const
    {
      return id::ARM_PUMP_COMMAND == which_inner_;
    }
    inline void clear_arm_pump_command()
    {
      if(id::ARM_PUMP_COMMAND == which_inner_)
      {
        which_inner_ = id::NOT_SET;
        inner_.arm_pump_command_.~ArmPumpCommand();
      }
    }
    inline void set_arm_pump_command(const ArmPumpCommand& value)
    {
      if(id::ARM_PUMP_COMMAND != which_inner_)
      {
        init_inner(id::ARM_PUMP_COMMAND);
      }
      inner_.arm_pump_command_ = value;
    }
    inline void set_arm_pump_command(const ArmPumpCommand&& value)
    {
      if(id::ARM_PUMP_COMMAND != which_inner_)
      {
        init_inner(id::ARM_PUMP_COMMAND);
      }
      inner_.arm_pump_command_ = value;
    }
    inline ArmPumpCommand& mutable_arm_pump_command()
    {
      if(id::ARM_PUMP_COMMAND != which_inner_)
      {
        init_inner(id::ARM_PUMP_COMMAND);
      }
      return inner_.arm_pump_command_;
    }
    inline const ArmPumpCommand& get_arm_pump_command() const { return inner_.arm_pump_command_; }
    inline const ArmPumpCommand& arm_pump_command() const { return inner_.arm_pump_command_; }

    inline bool has_hat_position_command() const
    {
      return id::HAT_POSITION_COMMAND == which_inner_;
    }
    inline void clear_hat_position_command()
    {
      if(id::HAT_POSITION_COMMAND == which_inner_)
      {
        which_inner_ = id::NOT_SET;
        inner_.hat_position_command_.~HatPositionCommand();
      }
    }
    inline void set_hat_position_command(const HatPositionCommand& value)
    {
      if(id::HAT_POSITION_COMMAND != which_inner_)
      {
        init_inner(id::HAT_POSITION_COMMAND);
      }
      inner_.hat_position_command_ = value;
    }
    inline void set_hat_position_command(const HatPositionCommand&& value)
    {
      if(id::HAT_POSITION_COMMAND != which_inner_)
      {
        init_inner(id::HAT_POSITION_COMMAND);
      }
      inner_.hat_position_command_ = value;
    }
    inline HatPositionCommand& mutable_hat_position_command()
    {
      if(id::HAT_POSITION_COMMAND != which_inner_)
      {
        init_inner(id::HAT_POSITION_COMMAND);
      }
      return inner_.hat_position_command_;
    }
    inline const HatPositionCommand& get_hat_position_command() const { return inner_.hat_position_command_; }
    inline const HatPositionCommand& hat_position_command() const { return inner_.hat_position_command_; }

    inline bool has_hat_pump_command() const
    {
      return id::HAT_PUMP_COMMAND == which_inner_;
    }
    inline void clear_hat_pump_command()
    {
      if(id::HAT_PUMP_COMMAND == which_inner_)
      {
        which_inner_ = id::NOT_SET;
        inner_.hat_pump_command_.~HatPumpCommand();
      }
    }
    inline void set_hat_pump_command(const HatPumpCommand& value)
    {
      if(id::HAT_PUMP_COMMAND != which_inner_)
      {
        init_inner(id::HAT_PUMP_COMMAND);
      }
      inner_.hat_pump_command_ = value;
    }
    inline void set_hat_pump_command(const HatPumpCommand&& value)
    {
      if(id::HAT_PUMP_COMMAND != which_inner_)
      {
        init_inner(id::HAT_PUMP_COMMAND);
      }
      inner_.hat_pump_command_ = value;
    }
    inline HatPumpCommand& mutable_hat_pump_command()
    {
      if(id::HAT_PUMP_COMMAND != which_inner_)
      {
        init_inner(id::HAT_PUMP_COMMAND);
      }
      return inner_.hat_pump_command_;
    }
    inline const HatPumpCommand& get_hat_pump_command() const { return inner_.hat_pump_command_; }
    inline const HatPumpCommand& hat_pump_command() const { return inner_.hat_pump_command_; }

    inline bool has_io_request() const
    {
      return id::IO_REQUEST == which_inner_;
    }
    inline void clear_io_request()
    {
      if(id::IO_REQUEST == which_inner_)
      {
        which_inner_ = id::NOT_SET;
        inner_.io_request_ = static_cast<IORequest>(0);
      }
    }
    inline void set_io_request(const IORequest& value)
    {
      if(id::IO_REQUEST != which_inner_)
      {
        init_inner(id::IO_REQUEST);
      }
      inner_.io_request_ = value;
    }
    inline void set_io_request(const IORequest&& value)
    {
      if(id::IO_REQUEST != which_inner_)
      {
        init_inner(id::IO_REQUEST);
      }
      inner_.io_request_ = value;
    }
    inline const IORequest& get_io_request() const { return inner_.io_request_; }
    inline IORequest io_request() const { return inner_.io_request_; }


    ::EmbeddedProto::Error serialize(::EmbeddedProto::WriteBufferInterface& buffer) const override
    {
      ::EmbeddedProto::Error return_value = ::EmbeddedProto::Error::NO_ERRORS;

      switch(which_inner_)
      {
        case id::SEQUENCE_COMMAND:
          if(has_sequence_command() && (::EmbeddedProto::Error::NO_ERRORS == return_value))
          {
            return_value = inner_.sequence_command_.serialize_with_id(static_cast<uint32_t>(id::SEQUENCE_COMMAND), buffer, true);
          }
          break;

        case id::ARM_POSITION_COMMAND:
          if(has_arm_position_command() && (::EmbeddedProto::Error::NO_ERRORS == return_value))
          {
            return_value = inner_.arm_position_command_.serialize_with_id(static_cast<uint32_t>(id::ARM_POSITION_COMMAND), buffer, true);
          }
          break;

        case id::ARM_PUMP_COMMAND:
          if(has_arm_pump_command() && (::EmbeddedProto::Error::NO_ERRORS == return_value))
          {
            return_value = inner_.arm_pump_command_.serialize_with_id(static_cast<uint32_t>(id::ARM_PUMP_COMMAND), buffer, true);
          }
          break;

        case id::HAT_POSITION_COMMAND:
          if(has_hat_position_command() && (::EmbeddedProto::Error::NO_ERRORS == return_value))
          {
            return_value = inner_.hat_position_command_.serialize_with_id(static_cast<uint32_t>(id::HAT_POSITION_COMMAND), buffer, true);
          }
          break;

        case id::HAT_PUMP_COMMAND:
          if(has_hat_pump_command() && (::EmbeddedProto::Error::NO_ERRORS == return_value))
          {
            return_value = inner_.hat_pump_command_.serialize_with_id(static_cast<uint32_t>(id::HAT_PUMP_COMMAND), buffer, true);
          }
          break;

        case id::IO_REQUEST:
          if(has_io_request() && (::EmbeddedProto::Error::NO_ERRORS == return_value))
          {
            EmbeddedProto::uint32 value = 0;
            value.set(static_cast<uint32_t>(inner_.io_request_));
            return_value = value.serialize_with_id(static_cast<uint32_t>(id::IO_REQUEST), buffer, true);
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
          case id::SEQUENCE_COMMAND:
            return_value = deserialize_inner(id::SEQUENCE_COMMAND, inner_.sequence_command_, buffer, wire_type);

            break;

          case id::ARM_POSITION_COMMAND:
            return_value = deserialize_inner(id::ARM_POSITION_COMMAND, inner_.arm_position_command_, buffer, wire_type);

            break;

          case id::ARM_PUMP_COMMAND:
            return_value = deserialize_inner(id::ARM_PUMP_COMMAND, inner_.arm_pump_command_, buffer, wire_type);

            break;

          case id::HAT_POSITION_COMMAND:
            return_value = deserialize_inner(id::HAT_POSITION_COMMAND, inner_.hat_position_command_, buffer, wire_type);

            break;

          case id::HAT_PUMP_COMMAND:
            return_value = deserialize_inner(id::HAT_PUMP_COMMAND, inner_.hat_pump_command_, buffer, wire_type);

            break;

          case id::IO_REQUEST:
            if(::EmbeddedProto::WireFormatter::WireType::VARINT == wire_type)
            {
              uint32_t value = 0;
              return_value = ::EmbeddedProto::WireFormatter::DeserializeVarint(buffer, value);
              if(::EmbeddedProto::Error::NO_ERRORS == return_value)
              {
                set_io_request(static_cast<IORequest>(value));
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
      clear_inner();

    }

    private:



      id which_inner_ = id::NOT_SET;
      union inner
      {
        inner() {}
        ~inner() {}
        SequenceCommand sequence_command_;
        ArmPositionCommand arm_position_command_;
        ArmPumpCommand arm_pump_command_;
        HatPositionCommand hat_position_command_;
        HatPumpCommand hat_pump_command_;
        IORequest io_request_;
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
          case id::SEQUENCE_COMMAND:
            new(&inner_.sequence_command_) SequenceCommand;
            which_inner_ = id::SEQUENCE_COMMAND;
            break;

          case id::ARM_POSITION_COMMAND:
            new(&inner_.arm_position_command_) ArmPositionCommand;
            which_inner_ = id::ARM_POSITION_COMMAND;
            break;

          case id::ARM_PUMP_COMMAND:
            new(&inner_.arm_pump_command_) ArmPumpCommand;
            which_inner_ = id::ARM_PUMP_COMMAND;
            break;

          case id::HAT_POSITION_COMMAND:
            new(&inner_.hat_position_command_) HatPositionCommand;
            which_inner_ = id::HAT_POSITION_COMMAND;
            break;

          case id::HAT_PUMP_COMMAND:
            new(&inner_.hat_pump_command_) HatPumpCommand;
            which_inner_ = id::HAT_PUMP_COMMAND;
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
          case id::SEQUENCE_COMMAND:
            inner_.sequence_command_.~SequenceCommand(); // NOSONAR Unions require this.
            break;
          case id::ARM_POSITION_COMMAND:
            inner_.arm_position_command_.~ArmPositionCommand(); // NOSONAR Unions require this.
            break;
          case id::ARM_PUMP_COMMAND:
            inner_.arm_pump_command_.~ArmPumpCommand(); // NOSONAR Unions require this.
            break;
          case id::HAT_POSITION_COMMAND:
            inner_.hat_position_command_.~HatPositionCommand(); // NOSONAR Unions require this.
            break;
          case id::HAT_PUMP_COMMAND:
            inner_.hat_pump_command_.~HatPumpCommand(); // NOSONAR Unions require this.
            break;
          case id::IO_REQUEST:
      	  inner_.io_request_ = static_cast<IORequest>(0);
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

#endif // IOBOARDCOMMUNICATIONDOWN_H