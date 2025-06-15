package inet.routing.fsr;
import inet.applications.contract.IApp;

simple Fsr like IApp
{
    parameters:
        @class("fsr::Fsr");
        @display("i=block/routing");
        double lifeInt @unit(s) = default(0.5s);
        double updateInt @unit(s) = default(0.5s);
        double jitter @unit(s) = default(50ms);
        double waitTime @unit(s) = default(4s);
        double helloInt @unit(s) = default(0.5s);
        string ifModule = default("^.interfaceTable");
        string rtModule = default("^.ipv4.routingTable");
        string netModule = default("^.ipv4.ip");
        string ifName = default("wlan0");
    gates:
        input socketIn;
        output socketOut;
}
