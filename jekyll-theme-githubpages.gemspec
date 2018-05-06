Gem::Specification.new do |spec|
  spec.name          = "jekyll-theme-githubpages"
  spec.version       = "1.0.0"
  spec.authors       = ["Olivia Zoe"]
  spec.email         = ["zoe.i2k1@gmail.com"]
 
  spec.summary       = %q{Theme for GitHub pages.}
  spec.description   = "A necessary (?) description for the theme."
  spec.homepage      = "https://lunarwatcher.github.io"
  spec.license       = "Unlicense"
 
  spec.files         = git ls-files -z.split("\x0").select { |f| f.match(%r{^(assets|_layouts|_includes|_sass|css|LICENSE)}i) }
 
  spec.add_runtime_dependency "jekyll-seo-tag", "~> 2.0"
 
  spec.add_development_dependency "jekyll", "~> 3.3"
  spec.add_development_dependency "bundler", "~> 1.12"
end