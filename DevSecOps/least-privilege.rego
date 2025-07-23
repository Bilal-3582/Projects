package policy

deny[msg] {
  input.resource == "aws_iam_policy"
  input.effect == "Allow"
  input.action == "*"
  msg := "Least privilege violated: Wildcard 'action' not allowed"
}
