/*
    Copyright (C) 2014-2016 Islog

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

#include "DBService.hpp"
#include "DatabaseTracer.hpp"
#include "Group_odb.h"
#include "OptionalTransaction.hpp"
#include "User_odb.h"
#include "tools/log.hpp"
#include <odb/database.hxx>

using namespace Leosac;


DBService::DBService(DBPtr db)
    : database_(db)
{
}

DBPtr DBService::db() const
{
    return database_;
}

size_t DBService::operation_count() const
{
    auto tracer = dynamic_cast<db::DatabaseTracer *>(database_->tracer());
    ASSERT_LOG(tracer, "No (valid?) tracer object on the database.");
    return tracer->count();
}

Auth::GroupPtr DBService::find_group_by_id(const Auth::GroupId &id)
{
    db::OptionalTransaction t(database_->begin());
    return database_->find<Auth::Group>(id);
}

Auth::UserPtr DBService::find_user_by_id(const Auth::UserId &id)
{
    db::OptionalTransaction t(database_->begin());
    return database_->find<Auth::User>(id);
}

Auth::UserGroupMembershipPtr
DBService::find_membership_by_id(const Auth::UserGroupMembershipId &id)
{
    db::OptionalTransaction t(database_->begin());
    return database_->find<Auth::UserGroupMembership>(id);
}