# Using SSH agents, and specifying which SSH key to use with pass-cli

This TIL assumes Proton Pass, but I hear the same strategy works with a few other password managers

Starting the agent (vault-scoped):

```bash
pass-cli ssh-agent start --vault-name Work
```

However, the neater part imo is how you configure it to work. This is what part of my `.ssh/config` looked like before SSH agents:
```ssh-config
Host github.com
  User git
  IdentityFile ~/.ssh/github
```

This cannot be used directly with SSH agents, because for obvious reasons, SSH agents make the IdentityFile not a file anymore. However, as far as I can tell anyway, the `IdentityFile` still needs to be a file. The `pass://` URL scheme `pass-cli` uses does not work either.

The fix is to use the public key instead:
```ssh-config
Host github.com
  User git
  IdentityFile ~/.ssh/github.pub
```

This relays the public key to the SSH agent, and it's tied to the corresponding private key within the agent. That forces the specific SSH key to be used, which is what allows multi-account SSH setups to continue to work with an SSH agent.

Using the public key as the `IdentityFile` seems to be the SSH agent way to specify which IdentityFile to use rather than trying all of them.
