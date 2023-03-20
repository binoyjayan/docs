
# Documentation
# https://registry.terraform.io/providers/hashicorp/aws/latest/docs


# required_providers can be used in terraform 0.13 and later
terraform {
  required_providers {
    aws = {
      source  = "hashicorp/aws"
      version = "~> 4.0"
    }
  }
}

# Select provider
provider "aws" {
  region = "us-east-1"
}

# Create resources within a provider
# resource "<provider>_<resource-type>" "name" {
  # config options
  # key = value
# }

# Create an EC2 instance [ Search for 'aws_instance' in EC2/Resources ]
# Note that the name here is for reference within terraform.
resource "aws_instance" "my-vm" {
  ami           = "ami-0557a15b87f6559cf"
  instance_type = "t3.micro"

  tags = {
    Name = "Basic Example - Intro"
    CreatedBy = "bjayan"
  }
}


# terraform init
# terraform plan
# terraform apply
# terraform destroy

# Directories and files

# .terraform               : Store plugin for all of the providers (terraform init)
# terraform.tfstate        : JSON blob of the state
# terraform.tfstate.backup : Backup of the file
