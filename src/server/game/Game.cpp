#include <Game.h>

template <typename T>
void addComponent(Entity* e, luabridge::LuaRef& componentTable) {
    e->addComponent(std::type_index(typeid(T)), new T(componentTable));
}

Entity* loadEntity(lua_State* L, const std::string& type) {
    using namespace luabridge;
    auto e = new Entity();
    e->setType(type);
    auto v = luah::getTableKeys(L, type);
    LuaRef entityTable = getGlobal(L, type.c_str());
    for (auto& componentName : v) {
        if (componentName == "GraphicsComponent") {
            LuaRef gcTable = entityTable["GraphicsComponent"];
            addComponent<GraphicsComponent>(e, gcTable);
        } else if (componentName == "NpcComponent") {
            LuaRef npccTable = entityTable["NpcComponent"];
            addComponent<NpcComponent>(e, npccTable);
        }

        std::cout << "Added " << componentName << " to " << type << std::endl;
    }
    return e;
}

bool Game::Initialize()
{

    //doOldLuaStuff();

    std::string filename = "../src/server/game/scripts/ghost.lua";

    // L = luabridge::luaL_newstate();
    // luaL_openlibs(L);

    // //luah::loadScript(L, "ghost.lua");
    // luaL_dofile(L, filename.c_str());
    // lua_pcall(L, 0, 0, 0);

    // if( luaL_loadfile(L, filename.c_str()) ||
    //     lua_pcall(L, 0, 0, 0)
    //     )
    // {
    //     printf("Script %s did not load properly!\n", filename.c_str());
    //     return false;
    // }
    // luah::loadGetKeysFunction(L);


    //auto e = loadEntity(L, "ghost");

}

void Game::handleMessage(std::string message)
{
    /* Handle the message */

    /* Clear the message*/


    if(message == "create")
    {

        
        lua_State* L = luaL_newstate();
        luaL_openlibs(L);

        luah::loadScript(L, "../src/server/game/scripts/ghost.lua");
        luah::loadGetKeysFunction(L);

        auto e = loadEntity(L, "ghost");
        auto npcc = e->get<NpcComponent>();
        std::cout << e->getType() << " says: " << npcc->getPhrase() << std::endl;

        lua_close(L);
        delete e;






        // Entity* testEntity = new Entity();

        // /* Create graphics component */
        // GraphicsComponent* testGraphicsComponent = new GraphicsComponent;
        // testGraphicsComponent->setFileName("test.png");
        // testEntity->addComponent(std::type_index(typeid(GraphicsComponent)), testGraphicsComponent);
        // testGraphicsComponent->getFileName();

        // /* Create Npc component */
        // NpcComponent* testNpc = new NpcComponent;
        // testNpc->setPhrase("I'm a test Npc!");
        // testEntity->addComponent(std::type_index(typeid(NpcComponent)), testNpc);
        // testNpc->getPhrase();

       

        message.clear();
    }

}

void Game::Update()
{
	
}

void Game::Close()
{

}

// bool Game::doOldLuaStuff()
// {

//     std::string fileName = "../src/server/game/scripts/script.lua";

//     luaState = luabridge::luaL_newstate();
//     luaL_dofile(luaState, fileName.c_str());
//     luaL_openlibs(luaState);
//     lua_pcall(luaState, 0, 0, 0);

//     if( luaL_loadfile(luaState, fileName.c_str()) ||
//         lua_pcall(luaState, 0, 0, 0)
//         )
//     {
//         printf("Script %s did not load properly!\n", fileName.c_str());
//         return false;
//     }

//     luabridge::LuaRef testString = getGlobal(luaState, "testString");
//     luabridge::LuaRef testNum = getGlobal(luaState, "number");

//     std::string luaString;
//     if(testString.isString())
//         luaString = testString.cast<std::string>();
//     else
//     {
//         printf("Variables not found!\n");
//         return false;
//     }

//     int answer;
//     if(!testNum.isNil())
//         answer = testNum.cast<int>();
//     else
//     {
//         printf("Variables not found!\n");
//         return false;
//     }

//     std::cout << luaString << std::endl;
//     std::cout << "And here's our number:" << answer << std::endl;


//     luabridge::LuaRef testTable = getGlobal(luaState, "gameWorld");
//     luabridge::LuaRef testTitle = testTable["title"];
//     luabridge::LuaRef testWidth = testTable["width"];
//     luabridge::LuaRef testHeight = testTable["height"];
//     luabridge::LuaRef testDepth = testTable["depth"];

//     std::string titleString;
//     if(testTitle.isString())
//         titleString = testTitle.cast<std::string>();

//     int width, height, depth;
//     if( testWidth.isNil() || 
//         testHeight.isNil() ||
//         testDepth.isNil() )
//     {
//         printf("Variables not found!\n");
//     }
//     else
//     {
//         width = testWidth.cast<int>();
//         height = testHeight.cast<int>();
//         depth = testDepth.cast<int>();
//     }

//     printf("Title: %s \nwidth = %d \nheight = %d\ndepth = %d\n", titleString.c_str(), width, height, depth);

// }