/*
    Copyright (C) 2014-2015 Islog

    This file is part of Leosac.

    Leosac is free software: you can redistribute it and/or modify
    it under the terms of the GNU Affero General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Leosac is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU Affero General Public License for more details.

    You should have received a copy of the GNU Affero General Public License
    along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#include <chrono>
#include <memory>
#include <map>
#include <vector>
#include "core/auth/Interfaces/IAccessProfile.hpp"
#include "core/auth/AuthTarget.hpp"
#include "tools/SingleTimeFrame.hpp"

namespace Leosac
{
    namespace Auth
    {
        class SimpleAccessProfile;
        using SimpleAccessProfilePtr = std::shared_ptr<SimpleAccessProfile>;

        /**
        * Concrete implementation of a simple access control class.
        */
        class SimpleAccessProfile : public IAccessProfile
        {
        public:
            virtual bool isAccessGranted(const std::chrono::system_clock::time_point &date,
                     AuthTargetPtr target) override;

            /**
            * Add range in which access is allowed.
            * @param target door we target. if this is null, it means this is a default access rule.
            */
            virtual void addAccessHour(AuthTargetPtr target,
                    int day, int start_hour, int start_min, int end_hour, int end_min);

            /**
            * Adds a time frame for a target.
            */
            virtual void addAccessTimeFrame(AuthTargetPtr target, const Tools::SingleTimeFrame& tf);

            /**
            * Provide informations about time frames that apply to non-specific door (ie when target is nullptr).
            */
            virtual const std::vector<Tools::SingleTimeFrame>& defaultTimeFrames() const;

            /**
            * Provide informations about the doors specific timeframe.
            */
            virtual const std::map<std::string, std::vector<Tools::SingleTimeFrame>>& timeFrames() const;

        protected:
            /**
            * Map target name to target's time frame.
            */
            std::map<std::string, std::vector<Tools::SingleTimeFrame>> time_frames_;

            /**
            * Time frames to use when we have nothing for a specific target.
            */
            std::vector<Tools::SingleTimeFrame> default_time_frames_;
        };
    }
}
