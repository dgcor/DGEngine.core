#pragma once

#include "Action.h"
#include "Game.h"
#include "GameUtils.h"
#include "Game/Level.h"

class ActLevelPause : public Action
{
private:
	std::string id;
	bool pause;

public:
	ActLevelPause(const std::string_view id_, bool pause_) : id(id_), pause(pause_) {}

	bool execute(Game& game) noexcept override
	{
		auto level = game.Resources().getLevel(id);
		if (level != nullptr)
		{
			level->Pause(pause);
		}
		return true;
	}
};

class ActLevelSave : public Action
{
private:
	std::string id;
	std::string file;
	Save::Properties props;

public:
	ActLevelSave(const std::string_view id_, const std::string_view file_,
		Save::Properties&& props_) : id(id_), file(file_), props(std::move(props_)) {}

	bool execute(Game& game) noexcept override
	{
		auto level = game.Resources().getLevel(id);
		if (level != nullptr)
		{
			level->save(GameUtils::replaceStringWithVarOrProp(file, game), props, game);
		}
		return true;
	}
};

class ActLevelSetShader : public Action
{
private:
	std::string id;
	std::string idShader;

public:
	ActLevelSetShader(const std::string_view id_, const std::string_view idShader_)
		: id(id_), idShader(idShader_) {}

	bool execute(Game& game) override
	{
		auto level = game.Resources().getLevel(id);
		if (level != nullptr)
		{
			auto shader = game.Resources().Shaders().get(idShader);
			level->setShader(shader);
		}
		return true;
	}
};
