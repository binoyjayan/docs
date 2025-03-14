.PHONY: up
up:
	sudo ip netns add red
	sudo ip netns add blue
	@echo "creating bridge network"
	sudo ip link add vnet-0 type bridge
	@echo "creating veth pairs for connecting the namespaces to vnet-0"
	sudo ip link add veth-red type veth peer name veth-red-br
	sudo ip link add veth-blue type veth peer name veth-blue-br
	@echo "connecting the namespaces to the bridge vnet-0"
	sudo ip link set veth-red netns red
	sudo ip link set veth-red-br master vnet-0
	sudo ip link set veth-blue netns blue
	sudo ip link set veth-blue-br master vnet-0
	@echo "setting the ip addresses"
	sudo ip -n red  addr add 192.168.15.2/24 dev veth-red
	sudo ip -n blue addr add 192.168.15.3/24 dev veth-blue
	sudo ip addr add 192.168.15.1/24 dev vnet-0
	@echo "setting the interfaces up"
	sudo ip link set dev vnet-0 up
	sudo ip link set veth-red-br up
	sudo ip link set veth-blue-br up
	sudo ip -n red  link set veth-red  up
	sudo ip -n blue link set veth-blue up
	@echo "validating the configuration"
	sudo ip netns exec red  ping -c 1 192.168.15.3
	sudo ip netns exec blue ping -c 1 192.168.15.2
	sudo ip netns exec red arp
	sudo ip netns exec blue arp

.PHONY: down
down:
	# peer links are auto-deleted
	sudo ip -n red link del veth-red
	sudo ip -n blue link del veth-blue
	sudo ip link del vnet-0
	sudo ip netns del red
	sudo ip netns del blue
