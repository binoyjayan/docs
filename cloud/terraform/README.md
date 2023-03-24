
## Terraform

### Terraform base commands

Initialize directory

```
terraform init
```

Perform dry run
```
terraform plan
```

Apply changes
```
terraform apply
terraform apply -auto-approve
```

Destroy deployment
```
terraform destroy
terraform destroy -auto-approve
```

Apply without prompt for confirmation
```
terraform apply -auto-approve
```

Apply with variable file
```
terraform apply -var-file variables.tfvars
terraform apply -var-file variables.tfvars -auto-approve
```

### Terraform state commands

List terraform state

```
terraform state
terraform state list
terraform state show <item-in-list>
```

List terraform output

```
terraform output
```

### Terraform selective apply / destroy

```
terraform state list
terraform destroy <item-in-list>
terraform destroy <item-in-list> -auto-approve

terraform apply <resource-name> -auto-approve
```



