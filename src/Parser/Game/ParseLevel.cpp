#include "ParseLevel.h"
#include "Game.h"
#include "Game/Level.h"
#include "Json/JsonUtils.h"
#include "Parser/Utils/ParseUtils.h"

namespace Parser
{
	using namespace rapidjson;
	using namespace std::literals;

	void parseLevel(Game& game, const Value& elem)
	{
		auto id = getStringViewKey(elem, "id");
		auto level = game.Resources().getLevel(id);
		if (level == nullptr)
		{
			if (isValidId(id) == false)
			{
				return;
			}
			auto levelPtr = std::make_shared<Level>();
			game.Resources().addDrawable(id, levelPtr, true, getStringViewKey(elem, "resource"));
			level = levelPtr.get();
			game.Resources().setCurrentLevel(level);
			level->Id(id);
			level->setShader(game.Shaders().Level);
		}

		if (elem.HasMember("name"sv) == true)
		{
			level->Name(getStringViewVal(elem["name"sv]));
		}

		if (getBoolKey(elem, "init") == true)
		{
			level->Init(game);
		}
	}
}
