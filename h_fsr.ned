package inet.routing.fsr;

import inet.networklayer.configurator.ipv4.Ipv4NetworkConfigurator;
import inet.node.contract.INetworkNode;
import inet.physicallayer.wireless.common.contract.packetlevel.IRadioMedium;
import inet.visualizer.contract.IIntegratedVisualizer;
import inet.routing.fsr.FsrRouter;
import inet.environment.common.PhysicalEnvironment;

network h_fsr
{
    parameters:
        int numHosts = default(10);
        @display("bgb=650,500;bgg=100,1,grey95");
        @figure[title](type=label; pos=0,-1; anchor=sw; color=darkblue);

        @figure[rcvdPkText](type=indicatorText; pos=380,20; anchor=w; font=,18; textFormat="packets received: %g"; initialValue=0);
        @statistic[packetReceived](source=hostB.app[0].packetReceived; record=figure(count); targetFigure=rcvdPkText);

    submodules:
        visualizer: <default(firstAvailableOrEmpty("IntegratedCanvasVisualizer"))> like IIntegratedVisualizer if typename != "" {
            @display("p=580,125");
        }
        configurator: Ipv4NetworkConfigurator {
            @display("p=580,200");
        }
        radioMedium: <default("UnitDiskRadioMedium")> like IRadioMedium {
            @display("p=580,275");
        }
        hostA: <default("WirelessHost")> like INetworkNode {
            @display("p=100,0");
            @display("i=misc/drone");
        }
        hostB: <default("WirelessHost")> like INetworkNode {
            @display("p=100,100");
            @display("i=misc/laptop2");
        }
        host[numHosts]: <default("WirelessHost")> like INetworkNode {
            @display("i=misc/smartphone");
        }
    connections allowunconnected:
} 