/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llacsivy <llacsivy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 17:45:26 by llacsivy          #+#    #+#             */
/*   Updated: 2025/04/26 17:45:35 by llacsivy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Channel.hpp"
#include "../include/IChannel.hpp"
#include "../include/channelHelperFcts.hpp"
#include "../include/Server.hpp"

Channel::Channel()
	:	_name(""), _topic(""), _isInviteOnly(false), \
		_hasPassword(false), _password(""), _userLimit(0), \
		_onlyOperatorCanChangeTopic(true)
{
}
Channel::Channel(const std::string& name)
	:	_name(name),  _topic(""), _isInviteOnly(false), \
	_hasPassword(false), _password(""), _userLimit(0), \
	_onlyOperatorCanChangeTopic(true)
{
}

Channel::~Channel()
{
}

std::string Channel::getName() const
{
	return _name;
}

std::string Channel::getTopic() const
{
	return _topic;
}

void Channel::setTopic(const std::string& topic)
{
	_topic = topic;
}

std::vector<std::string> Channel::getUsers() const
{
	return _users;
}

std::vector<std::string> &Channel::getUsers()
{
	return _users;
}

void Channel::addUser(const std::string& user, IServer& server)
{
	std::string msg;
	auto it = std::find(_invitedUsers.begin(), _invitedUsers.end(), user);
	if (_isInviteOnly && it == _invitedUsers.end())
    {
		msg = ":" + IRCname + " " + IRCerror::ERR_INVITEONLYCHAN + \
        " " + user + " " + _name + " :Cannot join channel (+i)";
        server.sendToClient(user, msg);
        return;
    }
	if (_userLimit == 0 || _users.size() < _userLimit)
        _users.push_back(user);
    else
		msg = ":" + IRCname + " " + IRCerror::ERR_CHANNELISFULL + \
		" "  + user + " " + _name + " :Cannot join channel (+l)";
        server.sendToClient(user, msg);
}

void Channel::removeUser(const std::string& user)
{
	removeEntryFromVec(_users, user);
	removeEntryFromVec(_operators, user);
}

std::vector<std::string> Channel::getOperators() const
{
	return _operators;
}

void Channel::addOperator(const std::string& oper)
{
	auto it = std::find(_operators.begin(), _operators.end(), oper);
	if (it == _operators.end())
		_operators.push_back(oper);
}

void Channel::removeOperator(const std::string&oper)
{
	removeEntryFromVec(_operators, oper);
}

std::vector<std::string> Channel::getInvitedUsers() const
{
	return _invitedUsers;
}

void Channel::addInvitedUser(const std::string& user)
{
	_invitedUsers.push_back(user);
}

void Channel::removeInvitedUser(const std::string& user)
{
	removeEntryFromVec(_invitedUsers, user);
}

bool Channel::getHasPassword() const
{
	return _hasPassword;
}

void Channel::setHasPassword(bool hasPassword)
{
	_hasPassword = hasPassword;
}

bool Channel::getIsInviteOnly() const
{
	return _isInviteOnly;
}

void Channel::setIsInviteOnly(bool isInviteOnly)
{
	_isInviteOnly = isInviteOnly;
}

size_t Channel::getUserLimit() const
{
	return _userLimit;
}

void Channel::setUserLimit(size_t userLimit)
{
	_userLimit = userLimit;
}

bool Channel::isValidChannelName(const std::string& name)
{
	if (name.size() > 50 || name.empty())
		return false;
	if (name[0] != '#' && name[0] != '&' && name[0] != '+' && name[0] != '!')
		return false;
	for (size_t i = 0; i < name.size(); i++)
	{
		if (name[i] == ' ' || name[i] == ',' || name[i] == 7)
			return false;
	}
	return true;
}

bool Channel::isValidPassword(const std::string password)
{
	if (_password == password)
		return true;
	else
		return false;
}

std::string Channel::getPassword() const
{
	return _password;
}

void Channel::setPassword(const std::string& password)
{
	_password = password;
}

bool Channel::isUser(const std::string& user)
{
	return std::find(_users.begin(), _users.end(), user) != _users.end();
}
bool  Channel::isOperator(const std::string& user)
{
	return std::find(_operators.begin(), _operators.end(), user) \
		!= _operators.end();
}
bool  Channel::isInvitedUser(const std::string& user)
{
	return std::find(_invitedUsers.begin(), _invitedUsers.end(), user) \
		!= _invitedUsers.end();
}

bool Channel::getOnlyOperatorCanChangeTopic()
{
	return _onlyOperatorCanChangeTopic;
}

void Channel::setOnlyOperatorCanChangeTopic(bool OnlyOperatorCanChangeTopic)
{
	_onlyOperatorCanChangeTopic = OnlyOperatorCanChangeTopic;
}
