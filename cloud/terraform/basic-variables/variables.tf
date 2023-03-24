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

# String Variable
variable "test_subnet" {
    description = "cidr block for the subnet"
    # default = "10.0.1.0/24"
    type = string
}

# Array Variable
variable "mgmt_subnets" {
    description = "List of cidr blocks for the subnets"
    # default = ["10.0.20.0/24", "10.0.30.0/24"]
    type = list
}

# Object Variable
variable "capture_subnets" {
    description = "List of cidr blocks and name objects"    
    type = list
}


# Search for 'aws_vpc' under VPC
resource "aws_vpc" "test_vpc" {
  cidr_block = "10.0.0.0/16"
  tags = {
    Name = "Test VPC"
    CreatedBy = "bjayan"
  }
}

# Define subnet that uses a string variable
resource "aws_subnet" "test_subnet" {  
  vpc_id     = aws_vpc.test_vpc.id
  cidr_block = var.test_subnet

  tags = {
    Name = "Test Subnet"
    CreatedBy = "bjayan"
  }
}

# Define subnet that uses a list variable
resource "aws_subnet" "mgmt_subnet_1" {  
  vpc_id     = aws_vpc.test_vpc.id
  cidr_block = var.mgmt_subnets[0]

  tags = {
    Name = "MGMT Subnet1"
    CreatedBy = "bjayan"
  }
}

# Define subnet that uses a list variable
resource "aws_subnet" "mgmt_subnet_2" {  
  vpc_id     = aws_vpc.test_vpc.id
  cidr_block = var.mgmt_subnets[1]

  tags = {
    Name = "MGMT Subnet2"
    CreatedBy = "bjayan"
  }
}


# Define subnets that uses an object from a list of objects
resource "aws_subnet" "capture_subnet_1" {  
  vpc_id     = aws_vpc.test_vpc.id
  cidr_block = var.capture_subnets[0].cidr_block

  tags = {
    Name = var.capture_subnets[0].name
    CreatedBy = var.capture_subnets[0].owner
  }
}

# Define subnets that uses an object from a list of objects
resource "aws_subnet" "capture_subnet_2" {  
  vpc_id     = aws_vpc.test_vpc.id
  cidr_block = var.capture_subnets[1].cidr_block

  tags = {
    Name = var.capture_subnets[1].name
    CreatedBy = var.capture_subnets[1].owner
  }
}
