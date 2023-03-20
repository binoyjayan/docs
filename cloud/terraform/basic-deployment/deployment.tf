terraform {
  required_providers {
    aws = {
      source  = "hashicorp/aws"
      version = "~> 4.0"
    }
  }
}

provider "aws" {
  region = "us-east-1"
}

# Create VPC
resource "aws_vpc" "main" {
  cidr_block = "10.0.0.0/16"
  tags = {
    Name = "bjayan-test-vpc"
    CreatedBy = "bjayan"
  }
}

# Create Internet Gateway (IGW)
resource "aws_internet_gateway" "gw" {
  vpc_id = aws_vpc.main.id

  tags = {
    Name = "bjayan-test-igw"
    CreatedBy = "bjayan"
  }
}

# Create Custom route table
# This ensure that the traffic from our subnet can reach internet
resource "aws_route_table" "test_route" {
  vpc_id = aws_vpc.main.id

  route {
    # Send all ipv4 traffic in this subnet (here, all) to the internet gateway
    cidr_block = "0.0.0.0/0"
    gateway_id = aws_internet_gateway.gw.id
  }

  # IPv6 route
  route {
    ipv6_cidr_block        = "::/0"
    gateway_id = aws_internet_gateway.gw.id
  }

  tags = {
    Name = "bjayan-test-route-table"
    CreatedBy = "bjayan"
  }
}

# Create Subnet for hosting our Virtual Machine
resource "aws_subnet" "subnet_1" {
  vpc_id     = aws_vpc.main.id
  cidr_block = "10.0.1.0/24"
  availability_zone = "us-east-1a"

  tags = {
    Name = "bjayan-test-subnet"
    CreatedBy = "bjayan"
  }
}

# Associate subnet with Route table
resource "aws_route_table_association" "a" {
  subnet_id      = aws_subnet.subnet_1.id
  route_table_id = aws_route_table.test_route.id
}

# Create Security Group to allow port 22, 80, and 443
resource "aws_security_group" "allow_web" {
  name        = "allow_web"
  description = "Allow Web traffic and ssh"
  vpc_id      = aws_vpc.main.id

  ingress {
    description      = "HTTPS"
    # Range of ports to allow
    from_port        = 443
    to_port          = 443
    protocol         = "tcp"
    # Who can access it
    cidr_blocks      = ["0.0.0.0/0"]
    # ipv6_cidr_blocks = [aws_vpc.main.ipv6_cidr_block]
  }

  ingress {
    description      = "HTTP"
    from_port        = 80
    to_port          = 80
    protocol         = "tcp"
    # Who can access it
    cidr_blocks      = ["0.0.0.0/0"]
    # ipv6_cidr_blocks = [aws_vpc.main.ipv6_cidr_block]
  }

  ingress {
    description      = "SSH"
    from_port        = 22
    to_port          = 22
    protocol         = "tcp"
    # Who can access it
    cidr_blocks      = ["0.0.0.0/0"]
    # ipv6_cidr_blocks = [aws_vpc.main.ipv6_cidr_block]
  }

  egress {
    from_port        = 0
    to_port          = 0
    # '-1' means any protocol
    protocol         = "-1"
    cidr_blocks      = ["0.0.0.0/0"]
    ipv6_cidr_blocks = ["::/0"]
  }

  tags = {
    Name = "bjayan-sg-allow-web-ssh"
    CreatedBy = "bjayan"
  }
}


# Create a network interface with an IP in the subnet created above
resource "aws_network_interface" "test_nic" {
  subnet_id       = aws_subnet.subnet_1.id
  private_ips     = ["10.0.1.50"]
  # List of security groups
  security_groups = [aws_security_group.allow_web.id]
  # The section attachment is optional while creating NIC

  tags = {
    Name = "bjayan-test-nic"
    CreatedBy = "bjayan"
  }
}

# Create an EC2 instance
data "aws_ami" "ubuntu" {
  most_recent = true
  filter {
    name   = "name"
    values = ["ubuntu/images/hvm-ssd/ubuntu-focal-20.04-amd64-server-*"]
  }
  filter {
    name   = "virtualization-type"
    values = ["hvm"]
  }
  owners = ["099720109477"] # Canonical
}

resource "aws_instance" "web_server" {
  ami           = data.aws_ami.ubuntu.id
  instance_type = "t3.micro"
  # Use the same as the subnet
  availability_zone = "us-east-1a"
  key_name = "bjayan-ctapdev-aws"
  network_interface {
    device_index = 0
    network_interface_id = aws_network_interface.test_nic.id
  }
  
  user_data = <<EOF
#!/bin/bash
sudo apt update -y
sudo apt install -y apache2
sudo systemctl start apache2  
sudo bash -c 'echo Apache is running > /var/www/html/index.html'
EOF

  tags = {
    Name = "bjayan-test-instance"
    CreatedBy = "bjayan"
  }
}

# Assign an elastic IP address to the network interface
# EIP may require IGW to exist prior to association.
# Use depends_on to set an explicit dependency on the IGW
resource "aws_eip" "one" {
  # If the EIP is in a VPC
  vpc                       = true
  network_interface         = aws_network_interface.test_nic.id
  # Use the IP address of the NIC created before
  # associate_with_private_ip = "10.0.1.50"
  depends_on = [aws_internet_gateway.gw, aws_instance.web_server]
}

# Display the public IP
output "Public-IP" {
  value = aws_eip.one.public_ip
}

output "Image-ID" {  
  value = data.aws_ami.ubuntu.image_id
}

