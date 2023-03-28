---
title: Toolchain Setup
sidebar_label: Toolchain Setup
---

import Tabs from '@theme/Tabs';
import TabItem from '@theme/TabItem';

export const OsTabs = (props) => (<Tabs
groupId="operating-systems"
defaultValue="debian"
values={[
{label: 'VS Code & Docker', value: 'docker'},
{label: 'Debian/Ubuntu', value: 'debian'},
{label: 'Windows', value: 'win'},
{label: 'macOS', value: 'mac'},
{label: 'Raspberry OS', value: 'raspberryos'},
{label: 'Fedora', value: 'fedora'},
]
}>{props.children}</Tabs>);

This guide will show you how to set up a development environment for building ZMK locally.

## Install Dependencies

Click the operating system you are using. (The VS Code & Docker option can be used on any OS.)

<OsTabs>
<TabItem value="docker">

This option use the same [Docker image which is used by the GitHub action](https://github.com/zmkfirmware/zmk-docker) for local development. Beyond the benefits of [dev/prod parity](https://12factor.net/dev-prod-parity), this approach is also the easiest to set up. No toolchain or dependencies are necessary when using Docker; the container image you'll be using already has the toolchain installed and set up to use.

1. Install [Docker Desktop](https://www.docker.com/products/docker-desktop) for your operating system.
2. Install [Visual Studio Code](https://code.visualstudio.com/)
3. Install the [Remote - Containers extension](https://marketplace.visualstudio.com/items?itemName=ms-vscode-remote.remote-containers)

:::info
The docker container already includes `west`. Skip past the following section to [Get Source Code](#get-source-code).
:::

</TabItem>
<TabItem value="debian">

Open Zephyr's [Getting Started Guide](https://docs.zephyrproject.org/3.2.0/develop/getting_started/index.html) and follow the instructions under these sections:

- [Select and Update OS](https://docs.zephyrproject.org/3.2.0/develop/getting_started/index.html#select-and-update-os)
- [Install Dependencies](https://docs.zephyrproject.org/3.2.0/develop/getting_started/index.html#install-dependencies)
- [Install Zephyr SDK](https://docs.zephyrproject.org/3.2.0/develop/getting_started/index.html#install-zephyr-sdk)

Return to this guide once you are finished with each section.

</TabItem>
<TabItem value="win">

Open Zephyr's [Getting Started Guide](https://docs.zephyrproject.org/3.2.0/develop/getting_started/index.html) and follow the instructions under these sections:

- [Select and Update OS](https://docs.zephyrproject.org/3.2.0/develop/getting_started/index.html#select-and-update-os)
- [Install Dependencies](https://docs.zephyrproject.org/3.2.0/develop/getting_started/index.html#install-dependencies)
- [Install Zephyr SDK](https://docs.zephyrproject.org/3.2.0/develop/getting_started/index.html#install-zephyr-sdk)

Return to this guide once you are finished with each section.

`dfu-util` is required to flash devices that use DFU, but there is currently no maintained package for it on Chocolatey. [QMK Toolbox](https://github.com/qmk/qmk_toolbox) contains a working version of it though.

</TabItem>
<TabItem value="mac">

Open Zephyr's [Getting Started Guide](https://docs.zephyrproject.org/3.2.0/develop/getting_started/index.html) and follow the instructions under these sections:

- [Select and Update OS](https://docs.zephyrproject.org/3.2.0/develop/getting_started/index.html#select-and-update-os)
- [Install Dependencies](https://docs.zephyrproject.org/3.2.0/develop/getting_started/index.html#install-dependencies)
- [Install Zephyr SDK](https://docs.zephyrproject.org/3.2.0/develop/getting_started/index.html#install-zephyr-sdk)

Return to this guide once you are finished with each section.

</TabItem>
<TabItem value="raspberryos">

#### Install Base Dependencies

Open Zephyr's [Getting Started Guide](https://docs.zephyrproject.org/3.2.0/develop/getting_started/index.html) and follow the instructions for Ubuntu under these sections:

- [Select and Update OS](https://docs.zephyrproject.org/3.2.0/develop/getting_started/index.html#select-and-update-os)
- [Install Dependencies](https://docs.zephyrproject.org/3.2.0/develop/getting_started/index.html#install-dependencies)

Return to this guide once you are finished with each section.

#### Install Cross-Compile Toolchain

Because Raspberry OS runs on the same architecture (but different ABI) as ARM keyboard MCUs, the operating system's installed [cross compilers](https://docs.zephyrproject.org/3.2.0/develop/toolchains/other_x_compilers.html) can be used to target the different ABI. Building for non-ARM MCUs has not been tested.

First, the cross compiler should be installed:

```sh
sudo apt install gcc-arm-none-eabi
```

Next, we'll configure Zephyr with some [environment variables](https://docs.zephyrproject.org/3.2.0/develop/env_vars.html#env-vars) needed to find the cross compiler. Create a file named `~/.zephyrrc` if it doesn't exist, and add these lines to it:

```sh
export ZEPHYR_TOOLCHAIN_VARIANT=cross-compile
export CROSS_COMPILE=/usr/bin/arm-none-eabi-
```

</TabItem>
<TabItem value="fedora">

Follow Zephyr's [Install Linux Host Dependencies](https://docs.zephyrproject.org/3.2.0/develop/getting_started/installation_linux.html) documentation for Fedora.

</TabItem>
</OsTabs>

### Install West

`west` is the [Zephyr® Project's meta-tool](https://docs.zephyrproject.org/3.2.0/develop/west/index.html) used to configure and build Zephyr OS applications.

West can be installed by using the `pip` python package manager. The [Zephyr™ instructions](https://docs.zephyrproject.org/3.2.0/develop/west/install.html) are summarized here:

<Tabs
defaultValue="linux"
groupId="python-os"
values={[
{label: 'Linux', value: 'linux'},
{label: 'Windows', value: 'win'},
{label: 'macOS', value: 'mac'},
]}>
<TabItem value="linux">

Install west:

```sh
pip3 install --user -U west
```

Verify that west is installed:

```sh
west --version
```

This should print a message like "West version: v0.14.0". If it prints an error instead, make sure `~/.local/bin` is on your `PATH` environment variable. You can add it with these commands:

```sh
echo 'export PATH=~/.local/bin:"$PATH"' >> ~/.bashrc
source ~/.bashrc
```

</TabItem>
<TabItem value="win">

Install west:

```sh
pip3 install -U west
```

Verify that west is installed:

```sh
west --version
```

This should print a message like "West version: v0.14.0". If it prints an error instead, make sure that the Python scripts directory is on your `PATH` environment variable. You can add it by opening a PowerShell window and running the following commands:

```powershell
$Scripts = python -c "import sysconfig; print(sysconfig.get_path('scripts'))"
$Path = [Environment]::GetEnvironmentVariable('PATH', 'User')
[Environment]::SetEnvironmentVariable('PATH', "$Path;$Scripts", 'User')
$env:PATH += ";$Scripts"
```

</TabItem>
<TabItem value="mac">

Install west:

```sh
pip3 install -U west
```

</TabItem>
</Tabs>

## Get Source Code

Next, you'll need to clone the ZMK source repository if you haven't already. Navigate to the folder you would like to place your `zmk` directory in and run the following command:

```
git clone https://github.com/zmkfirmware/zmk.git
```

## Initialize & Update Zephyr Workspace

Since ZMK is built as a Zephyr™ application, the next step is
to use `west` to initialize and update your workspace. The ZMK
Zephyr™ application is in the `app/` source directory:

### Step into the repository

<OsTabs>
<TabItem value="debian">

```sh
cd zmk
```

</TabItem>
<TabItem value="raspberryos">

```sh
cd zmk
```

</TabItem>
<TabItem value="fedora">

```sh
cd zmk
```

</TabItem>
<TabItem value="mac">

```sh
cd zmk
```

</TabItem>
<TabItem value="win">

```sh
cd zmk
```

</TabItem>

<TabItem value="docker">

Open the `zmk` checkout folder in VS Code. The repository includes a configuration for containerized development, so an alert will pop up:

![VS Code Dev Container Configuration Alert](../assets/dev-setup/vscode_devcontainer.png)

Click `Reopen in Container` in order to reopen the VS Code with the running container.

The first time you do this on your machine, it will pull the docker image down from the registry and build the container. Subsequent launches are much faster!

:::caution
All subsequent steps must be performed from the VS Code terminal _inside_ the container.
:::

</TabItem>
</OsTabs>

### Initialize the Application

```sh
west init -l app/
```

### Update to Fetch Modules

```sh
west update
```

:::tip
This step pulls down quite a bit of tooling. Go grab a cup of coffee, it can take 10-15 minutes even on a good internet connection!
:::

:::info
If you're using Docker, you're done with setup! You must restart the container at this point. The easiest way to do so is to close the VS Code window, verify that the container has stopped in Docker Dashboard, and reopen the container with VS Code.

Once your container is restarted, proceed to [Building and Flashing](development/build-flash.md).
:::

### Export Zephyr CMake package

This allows CMake to load the code needed to build ZMK.

```sh
west zephyr-export
```

### Install Zephyr Python Dependencies

Some additional Python dependencies are listed in Zephyr's `scripts/requirements.txt` file.

<Tabs
defaultValue="linux"
groupId="python-os"
values={[
{label: 'Linux', value: 'linux'},
{label: 'Windows', value: 'win'},
{label: 'macOS', value: 'mac'},
]}>
<TabItem value="linux">

```sh
pip3 install --user -r zephyr/scripts/requirements.txt
```

</TabItem>
<TabItem value="win">

```sh
pip3 install -r zephyr/scripts/requirements.txt
```

</TabItem>
<TabItem value="mac">

```sh
pip3 install -r zephyr/scripts/requirements.txt
```

</TabItem>
</Tabs>
