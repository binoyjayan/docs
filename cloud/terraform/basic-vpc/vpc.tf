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

# Search for 'aws_vpc' under VPC
resource "aws_vpc" "test_vpc" {
  cidr_block = "10.0.0.0/16"
  tags = {
    Name = "Test VPC"
    CreatedBy = "bjayan"
  }
}

# Search for 'aws_subnet' under VPC
resource "aws_subnet" "subnet_1" {
  # Reference the vpc created above
  # <resource_type>.<resource_name>.<property>
  vpc_id     = aws_vpc.test_vpc.id
  cidr_block = "10.0.1.0/24"

  tags = {
    Name = "Test Subnet"
    CreatedBy = "bjayan"
  }
}
