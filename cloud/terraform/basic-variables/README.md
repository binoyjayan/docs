
## Variables

### Assign value via arguments

Assign variables via commandline arguments.

```
terraform apply -var "test_subnet=10.0.100.0/24"
```

### Assign value via file

Variables can be defined in a file.
By default terraform looks for a file named 'terraform.tfvars'

Or a custom file can be used like so:

```
terraform apply -var-file variables.tfvars
```

File contents:
```
test_subnet = "10.0.1.0/24"
```

