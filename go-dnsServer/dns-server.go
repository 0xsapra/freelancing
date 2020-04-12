package main


import (
	"fmt"

	"github.com/benburkert/dns"
)



func main() {
	fmt.Println("Hello world")

	zone := &dns.Zone{
		Origin: "localhost.",
		TTL:    5 * time.Minute,
		RRs: dns.RRSet{
			"alpha": []dns.Record{
				&dns.A{net.IPv4(127, 0, 0, 42).To4()},
				&dns.AAAA{net.ParseIP("::42")},
			},
		},
	}

	srv := &dns.Server{
		Addr:    ":53",
		Handler: zone,
	}

	go srv.ListenAndServe(ctx)

	mux := new(dns.ResolveMux)
	mux.Handle(dns.TypeANY, zone.Origin, zone)

	client := &dns.Client{
		Resolver: mux,
	}

	net.DefaultResolver = &net.Resolver{
		PreferGo: true,
		Dial:     client.Dial,
	}

	addrs, err := net.LookupHost("alpha.localhost")
	fmt.Println(addrs)
}