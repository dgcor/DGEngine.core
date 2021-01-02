#include "SaveLevel.h"
#include "FileUtils.h"
#include "Game/Level.h"
#include "SaveUtils.h"

using namespace rapidjson;
using namespace SaveUtils;

void Save::save(const std::string_view filePath, const Properties& props,
	const Game& game, const Level& level)
{
	StringBuffer buffer(0, std::numeric_limits<uint16_t>::max());
	PrettyWriter<StringBuffer> writer(buffer);
	writer.SetIndent(' ', 2);

	serialize(&writer, props, game, level);

	FileUtils::saveText(filePath, { buffer.GetString(), buffer.GetSize() });
}

void Save::serialize(void* serializeObj, const Properties& props,
	const Game& game, const Level& level)
{
	auto& writer = *((PrettyWriter<StringBuffer>*)serializeObj);

	// root
	writer.StartObject();

	writeKeyStringView(writer, "level");

	// level
	writer.StartObject();

	writeStringView(writer, "id", level.id);
	writeStringView(writer, "name", level.name);

	// level
	writer.EndObject();

	// root
	writer.EndObject();
}
