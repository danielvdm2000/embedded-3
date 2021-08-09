#include "mbed.h"
#include "EthernetInterface.h"
#include "Router.h"

#include "TemperatureController.h"
#include <map>

EthernetInterface net;

// typedef Response (*Resolver)(Request req);

// Response hej(Request req) {
//     Response res;

//     res.status(StatusCode::_200);
//     res.text("Hello world");

//     return res;
// };

int main()
{
    // std::map<std::string, Resolver> resolvers = {
    //     { "/hello", hej }
    // };

    // while(true) {
    //     Request req;
    //     Resolver resolver = resolvers.at("/hello");

    //     Response res = resolver(req);
    //     std::string result = res.build();

    //     printf("Result: %s\r\n", result.c_str());

    //     wait_us(1000000);
    // }

    Router router(&net);

    TemperatureController temperatureController;

    // std::map<std::string, RouteResolverFn> resolvers = {
    //     { "/hello", temperatureController.getTemperature }
    // };

    // while(true) {
    //     RouteResolverFn resolver = resolvers.at("/hello");

    //     Request req;

    //     printf("Resolving...\r\n");
    //     Response* res = resolver(req);
    //     printf("Resolved\r\n");

    //     printf("Building...");
    //     printf("Res: \n%s\r\n", res->build().c_str());
    //     printf("Build\r\n");

    //     wait_us(1000000);
    // }


    router.get("/temperature", temperatureController.getTemperature);
    router.post("/temperature", temperatureController.postTemperature);

    router.listen(80);
}