package inet.routing.fsr;

import inet.node.inet.AdhocHost;
import inet.routing.fsr.Fsr;

module FsrRouter extends AdhocHost {
    submodules:
        router: Fsr {
            @display("p=400,400");
        }
    connections:
        router.socketOut --> at.in++;
        router.socketIn <-- at.out++;
} 