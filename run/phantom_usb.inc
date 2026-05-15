

<!--
  !!! ОБЪЕДИНИТЬ VFS КОМПОНЕНТЫ !!!
-->

<!--
  Это нужно, потому что у нас две блочных сессии
  Если пойму, как их использовать в одном компоненте, то нужно объединять 
-->















































<!--
  Надо разобраться:
    - Для чего нужны все эти директории?
    - Где хранить директорию crypto?
    - Понадобятся ли другие директории?
-->

<start name="usb_sec" ram="4M">
  <binary name="usb_block"/>
  <provides> <service name="Block"/> </provides>
  <config label="usb_drive" report="yes" writeable="yes" interface="0"
          alt_setting="0" lun="0" reset_device="no" verbose_scsi="no"/>
  <route>
  <service name="Usb"> <child name="usb"/> </service>
  <service name="Report"> <child name="report_rom"/> </service>
  <any-service> <parent/> <any-child/> </any-service>
  </route>
</start>


<!--
<start name="usb_sec_fs" caps="120" ram="16M">
  <binary name="vfs"/>
  <provides>
    <service name="File_system"/>
  </provides>
  <config>
    <vfs>
      <dir name="usb">
        <fatfs block="default" writeable="yes"/>
      </dir>
      <dir name="dev">
        <jitterentropy/>
        <tresor_trust_anchor name="tresor_trust_anchor" storage_dir="/usb"/>
      </dir>
    </vfs>
    <default-policy root="/dev/tresor_trust_anchor" writeable="yes"/>
    <policy label="sequence -> ls_seq1 -> /" root="/usb"/>
    <policy label="sequence -> ls_seq2 -> /" root="/dev/tresor_trust_anchor"/>
  </config>
  <route>
    <service name="Block"> <child name="usb_sec"/> </service>
    <any-service> <parent/> </any-service>
  </route>
</start>
-->


<start name="usb_sec_fs" caps="120" ram="32M">
  <binary name="vfs"/>
  <provides>
    <service name="File_system"/>
  </provides>
  <config>
    <vfs>
      <dir name="usb">
        <fatfs block="default" writeable="yes"/>
      </dir>
      <!--
      <dir name="dev">
        <tresor_trust_anchor name="tresor_trust_anchor" storage_dir="/usb"/>
      </dir>
      -->
    </vfs>
    <default-policy root="/usb" writeable="yes"/>
  </config>
  <route>
    <service name="Block"> <child name="usb_sec"/> </service>
    <any-service> <parent/> </any-service>
  </route>
</start>


<!--
   		<dir name="dev">
   			<block name="block" block_buffer_count="128"/>
   		</dir>
      <dir name="drive">
        <lwext4 block_device="/dev/block" cache_write_back="no"
                expand_via_io="no" writeable="yes"
                reporting="yes"
                report_cache="yes"/>
      </dir>
    -->
<start name="se_vfs" ram="512M" caps="200">
  <binary name="vfs"/>
  <provides><service name="File_system"/></provides>
  <config verbose="yes">
  <!--
   	<vfs>
      <rump fs="ext2fs" ram="20M"/>
   	</vfs>
  -->
    <vfs>
      <dir name="dev">
          <block name="block" block_buffer_count="128"/>
        </dir>
        <dir name="drive">
          <lwext4 block_device="/dev/block" cache_write_back="no"
                  expand_via_io="yes" writeable="yes"
                  reporting="yes"
                  report_cache="no"/>
        </dir>
      </vfs>
    <default-policy root="/drive" writeable="yes"/>
  </config>
  <route>
    <service name="Block"> <child name="ahci"/> </service>
    <service name="Report"> <child name="report_rom"/> </service>
    <any-service> <parent/> <any-child/> </any-service>
  </route>
</start>


<!--
<start name="sequence" caps="200" ram="128M">
	<config>


      <start name="ls_seq1" ram="4M">
        <binary name="ls"/>
        <config>
          <libc stdout="/dev/log" stderr="/dev/log"/>
          <vfs>
          <dir name="dev"> <log/> </dir>
          <dir name="se_trust_anchor">
            <fs label="ta -> /"/>
          </dir>
        </vfs>
        </config>
        <route>
-->
          <!-- <service name="File_system"> <child name="usb_sec_fs"/> </service> -->
<!--
          <service name="Report"> <child name="report_rom"/> </service>
          <service name="PD">  <parent/> </service>
          <service name="ROM"> <parent/> </service>
          <service name="LOG"> <parent/> </service>
          <service name="CPU"> <parent/> </service>
        </route>
      </start>

-->
<!--
      <start name="ls_seq2" ram="4M">
        <binary name="ls"/>
        <config>
          <libc stdout="/dev/log" stderr="/dev/log"/>
          <vfs>
          <dir name="dev"> <log/> </dir>
          <dir name="se_trust_anchor">
            <fs label="ta -> /"/>
          </dir>
        </vfs>
        </config>
        <route>
          <service name="File_system"> <child name="usb_sec_fs"/> </service>
          <service name="Report"> <child name="report_rom"/> </service>
          <service name="PD">  <parent/> </service>
          <service name="ROM"> <parent/> </service>
          <service name="LOG"> <parent/> </service>
          <service name="CPU"> <parent/> </service>
        </route>
      </start>
-->

<!--
    <start name="se_tresor_init_trust_anchor" ram="4M">
      <config passphrase="foobar" trust_anchor_dir="/se_trust_anchor" verbose="yes">
        <vfs>
          <dir name="se_trust_anchor">
            <fs label="ta -> /"/>
          </dir>
        </vfs>
      </config>
      <route>
        <service name="PD">  <parent/> </service>
        <service name="ROM"> <parent/> </service>
        <service name="LOG"> <parent/> </service>
        <service name="CPU"> <parent/> </service>
      </route>
    </start>



    <start name="se_tresor_init" ram="4M">
      <config>
        <block-io type="vfs" path="/tresor.img"/> 
        <crypto path="/crypto"/> 
        <trust-anchor path="/se_trust_anchor"/> 
          <vfs>
            <fs buffer_size="1M"/>
						<tresor_crypto_aes_cbc name="crypto"/>
						<dir name="se_trust_anchor">
							<fs label="ta -> /"/>
						</dir>
          </vfs>
        <virtual-block-device max_lvl="2" degree="64" num_leaves="512" />
        <free-tree max_lvl="2" degree="64" num_leaves="2048" />
      </config>
      <route>
        <service name="PD">  <parent/> </service>
				<service name="ROM"> <parent/> </service>
				<service name="LOG"> <parent/> </service>
				<service name="CPU"> <parent/> </service>
      </route>
    </start>


    <start name="tresor_vfs" ram="200M" caps="200">
      <binary name="vfs"/>
      <provides><service name="File_system"/></provides>
      <config>
        <vfs>
          <dir name="dev">
            <block name="block" block_buffer_count="128"/>
          </dir>
          <dir name="drive">
            <lwext4 block_device="/dev/block" cache_write_back="no"
                    expand_via_io="no" writeable="yes"
                    reporting="yes"
                    external_cache_size="32M" report_cache="yes"/>
          </dir>
        </vfs>
        <default-policy root="/drive" writeable="yes"/>
      </config>
      <route>
        <service name="Block"> <child name="ahci"/> </service>
        <service name="Report"> <child name="report_rom"/> </service>
        <any-service> <parent/> <any-child/> </any-service>
      </route>
    </start>

  </config>
  <route>
    <service name="File_system" label_suffix="ta -> /"> <child name="usb_sec_fs"/> </service>
    <service name="File_system"> <child name="se_vfs"/> </service>
    <service name="PD">  <parent/> </service>
    <service name="ROM"> <parent/> </service>
    <service name="LOG"> <parent/> </service>
    <service name="CPU"> <parent/> </service>
    <any-service> <parent/> </any-service>
  </route>
</start>
-->





<start name="se_vault" caps="1500" ram="2000M">
  <provides>
    <service name="File_system"/>
  </provides>
	<config jitterentropy_available="yes">
		<vfs>
			<dir name="tresor">
				<fs label="tresor -> /"/>
			</dir>
		</vfs>
	</config>
	<route>

		<service name="File_system" label_prefix="se_tresor_trust_anchor_vfs -> storage_dir"> <child name="usb_sec_fs" identity="se_vault -> trust_anchor"/> </service>
		<service name="File_system" label_prefix="se_tresor_init ->">          <child name="se_vfs" identity="se_vault -> data"/> </service>
		<service name="File_system" label_prefix="tresor ->">               <child name="se_vfs" identity="se_vault -> data"/> </service>
		<service name="File_system" label_prefix="fs_query ->">             <child name="se_vfs" identity="se_vault -> data"/> </service>
		<service name="File_system" label_prefix="image_fs_query ->">       <child name="se_vfs" identity="se_vault -> data"/> </service>
		<service name="File_system" label_prefix="se_tresor_vfs -> tresor_fs"> <child name="se_vfs" identity="se_vault -> data"/> </service>
		<service name="File_system" label_prefix="truncate_file -> tresor"> <child name="se_vfs" identity="se_vault -> data"/> </service>
    <service name="File_system" label_prefix="init_flag -> tresor"> <child name="se_vfs" identity="se_vault -> data"/> </service>
		<service name="Timer"> <child name="timer"/> </service>
		<service name="PD"> <parent/> </service>
		<service name="ROM"> <parent/> </service>
		<service name="CPU"> <parent/> </service>
		<service name="LOG"> <parent/> </service>
		<service name="RM"> <parent/> </service>
    
    <any-service> <parent/> </any-service>
	</route>
</start>

    
    <!--
    <service name="Rtc"> <child name="pc_rtc"/> </service>
    <service name="Block" label_prefix="isomem ->"> <child name="ahci"/> </service>
    <service name="Gui"> <child name="nitpicker"/> </service>
    -->
		<!-- 
    <service name="ROM" label="ui_config"> <child name="dynamic_rom" label="file_vault_ui_config"/> </service>
		<service name="Report" label="ui_report"> <child name="report_rom"/> </service>
    -->



<!-- 
<start name="snapper" ram="400M" caps="200">
  <provides>
    <service name="Snapper"/>
  </provides>

  <config
      verbose="true"
      redundancy="2"
      integrity="true"
      max_snapshots="0"
      min_snapshots="0"
      threshold="1000"
      expiration="3600"
      bufsize="10M">

    <rtc/>

    <vfs>
      <fs/>	  
    </vfs>
  </config>
	<route>
-->
	<!--
		<service name="File_system"><child name="vfs"/></service>
	-->
<!--
		<service name="File_system"><child name="se_vault"/></service>
		<service name="Block"><child name="ahci"/></service>
		<any-service> <parent/> <any-child /> </any-service>
	</route>
</start>
-->




<start name="timer" caps="200" ram="1M">
			<resource name="CPU" quantum="5"/>
			<provides> <service name="Timer"/> </provides>
			<route>
				<service name="PD"> <parent/> </service>
				<service name="ROM"> <parent/> </service>
				<service name="LOG"> <parent/> </service>
				<service name="CPU"> <parent/> </service>
				<service name="IO_PORT"> <parent/> </service>
				<service name="IRQ"> <parent/> </service>
			</route>
		</start>

		<start name="dynamic_rom" caps="100" ram="4M">
			<provides><service name="ROM"/> </provides>
			<config verbose="yes">
				<rom name="file_vault_ui_config">
					<inline> <ui_config/> </inline>
					<sleep milliseconds="6000"/>
					<inline> <ui_config passphrase="abcdefgh" client_fs_size="1M" journaling_buf_size="1M"/> </inline>
					<sleep milliseconds="10000"/>
					<inline> <ui_config/> </inline>
					<sleep milliseconds="6000"/>
					<inline> <ui_config passphrase="00000001"/> </inline>
					<sleep milliseconds="6000"/>
					<inline> <ui_config/> </inline>
					<sleep milliseconds="6000"/>
					<inline> <ui_config passphrase="abcdefgh"/> </inline>
					<sleep milliseconds="600000"/>
				</rom>
			</config>
			<route>
				<service name="Timer"> <child name="timer"/> </service>
				<service name="PD">  <parent/> </service>
				<service name="ROM"> <parent/> </service>
				<service name="LOG"> <parent/> </service>
				<service name="CPU"> <parent/> </service>
			</route>
		</start>








<!--
<start name="se_data_vfs" ram="32M" caps="200">
  <binary name="vfs"/>
  <provides><service name="File_system"/></provides>
  <config>
    <vfs>
      <fs/>
    </vfs>
    <default-policy root="/" writeable="yes"/>
  </config>
  <route>
    <service name="File_system"> <child name="se_vfs"/> </service>
    <any-service><parent/></any-service>
  </route>
</start>
-->