FROM alpine:latest

# Set environment variables for ZSH with absolute path
ENV ZSH="/root/.oh-my-zsh"
ENV ZSH_CUSTOM="$ZSH/custom"

RUN apk update && apk add --no-cache \
    valgrind \
    gcc g++ make \
    lsof \
    vim git zsh curl && \
    # Install Oh My Zsh unattended
    sh -c "$(curl -fsSL https://raw.githubusercontent.com/ohmyzsh/ohmyzsh/master/tools/install.sh)" "" --unattended && \
    apk del curl && \
    # Install plugins
    git clone https://github.com/zsh-users/zsh-completions.git $ZSH_CUSTOM/plugins/zsh-completions && \
    git clone https://github.com/zsh-users/zsh-autosuggestions $ZSH_CUSTOM/plugins/zsh-autosuggestions && \
    git clone https://github.com/zsh-users/zsh-syntax-highlighting.git $ZSH_CUSTOM/plugins/zsh-syntax-highlighting && \
    # Update .zshrc to enable plugins
    sed -i 's/plugins=(git)/plugins=(git zsh-completions zsh-autosuggestions zsh-syntax-highlighting)/' /root/.zshrc

# Set Zsh as the default shell
CMD [ "zsh" ]