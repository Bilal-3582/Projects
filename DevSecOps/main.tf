provider "aws" {
  region = "us-east-1"
}

## ✅ Secure IAM Policy - follows least privilege principle
#resource "aws_iam_policy" "secure_policy" {
#  name        = "SecurePolicy"
#  description = "Policy with restricted actions and resources"
#
#  policy = jsonencode({
#    Version = "2012-10-17",
#    Statement = [
#      {
#        Effect   = "Allow"
#        Action   = [
#          "s3:ListBucket",
#          "s3:GetObject"
#        ]
#        Resource = [
#          "arn:aws:s3:::my-bucket",
#          "arn:aws:s3:::my-bucket/*"
#        ]
#      },
#      {
#        Effect   = "Allow"
#        Action   = [
#          "ec2:DescribeInstances",
#          "ec2:StartInstances"
#        ]
#        Resource = "*"
#      }
#    ]
#  })
#}


resource "aws_iam_policy" "secure_limited_policy" {
  name        = "SecureLimitedPolicy"
  description = "A policy with scoped permissions ."

  policy = jsonencode({
    Version = "2012-10-17",
    Statement = [
      {
        Effect   = "Allow",
        Action   = [
          "ec2:DescribeInstances",
          "s3:GetObject",
          "s3:ListBucket"
        ],
        Resource = [
          "arn:aws:s3:::my-bucket",
          "arn:aws:s3:::my-bucket/*",
          "arn:aws:ec2:us-east-1:123456789012:instance/*"
        ]
      }
    ]
  })
}



## ❌ Insecure IAM Policy - overly permissive (for security scanning demonstration)
#resource "aws_iam_policy" "insecure_policy" {
#  name        = "InsecurePolicy"
#  description = "Policy with wildcard actions and resources (violates least privilege)"
#
#  policy = jsonencode({
#    Version = "2012-10-17",
#    Statement = [
#      {
#        Effect   = "Allow",
#        Action   = "*",
#        Resource = "*"
#      }
#    ]
#  })
#}

## ❌ Hardcoded secret - violates secret management best practices
#variable "api_key" {
#  description = "API key (should not be hardcoded)"
#  type        = string
#  default     = ""  # This should be securely managed via environment variables or AWS Secrets Manager
#}
