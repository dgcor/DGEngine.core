#include "ParseActionGame.h"
#include "Actions/ActLevel.h"
#include "Utils/ParseUtils.h"
#include "Utils/Utils.h"

namespace Parser
{
	using namespace rapidjson;

	std::shared_ptr<Action> parseActionGameElem(Game& game,
		uint16_t nameHash16, const Value& elem)
	{
		switch (nameHash16)
		{
		case str2int16("level.pause"):
		{
			return std::make_shared<ActLevelPause>(
				getStringViewKey(elem, "level"),
				getBoolKey(elem, "pause", true));
		}
		case str2int16("level.save"):
		{
			return std::make_shared<ActLevelSave>(
				getStringViewKey(elem, "level"),
				getStringViewKey(elem, "file"),
				getVariablesMapKey(elem, "properties"));
		}
		case str2int16("level.setShader"):
		{
			return std::make_shared<ActLevelSetShader>(
				getStringViewKey(elem, "level"),
				getStringViewKey(elem, "shader"));
		}
		default:
			return nullptr;
		}
	}
}
