.PHONY: up
up:
	sudo ip netns add red
	sudo ip netns add blue
	sudo ip link add veth-red type veth peer name veth-blue
	sudo ip link set veth-red  netns red
	sudo ip link set veth-blue netns blue
	sudo ip -n red  addr add 192.168.15.2/24 dev veth-red
	sudo ip -n blue addr add 192.168.15.3/24 dev veth-blue
	sudo ip -n red  link set veth-red  up
	sudo ip -n blue link set veth-blue up
	sudo ip -n red  addr show dev veth-red
	sudo ip -n blue addr show dev veth-blue
	sudo ip netns exec red  ping -c 1 192.168.15.3
	sudo ip netns exec blue ping -c 1 192.168.15.2
	sudo ip netns exec red arp
	sudo ip netns exec blue arp

.PHONY: down
down:
    # peer link is auto-deleted
	sudo ip -n red link delete veth-red
	sudo ip netns del red
	sudo ip netns del blue
