#include "commands.h"

#include "pickle.h"

namespace ChromieTabs
{

UpdateTabNavigationCommand::UpdateTabNavigationCommand(const RawCommand &raw_cmd)
    : Command(raw_cmd)
{
    Pickle pickle(raw_cmd.content);
    auto it = pickle.get_iterator();
    it.read_int32(tab_id);
    it.read_int32(navigation_index);
    it.read_string(url);
    it.read_u16string(title);
}

}
