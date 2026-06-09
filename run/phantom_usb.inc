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


<start name="se_vault" caps="1500" ram="2000M">
  <exit propagate="yes"/>
  <provides>
    <service name="File_system"/>
  </provides>
	<config 
    jitterentropy_available="yes"
    fsck_apply="no"
  >
    <vfs/>
	</config>
	<route>
		<service name="Block" label_prefix="se_tresor_trust_anchor_vfs ->"> <child name="usb_sec" identity="se_vault -> trust_anchor"/> </service>
    <service name="Block" label_prefix="se_tresor_init ->">          <child name="nvme2" identity="se_vault -> data"/> </service>
		<service name="Block" label_prefix="tresor ->">               <child name="nvme2" identity="se_vault -> data"/> </service>
		<service name="Block" label_prefix="se_tresor_vfs ->"> <child name="nvme2" identity="se_vault -> data"/> </service>
    <service name="Block" label_prefix="init_flag ->"> <child name="nvme2" identity="se_vault -> data"/> </service>
		<service name="Timer"> <child name="timer"/> </service>
    <service name="Report"> <child name="report_rom"/> </service>
		<service name="PD"> <parent/> </service>
		<service name="ROM"> <parent/> </service>
		<service name="CPU"> <parent/> </service>
		<service name="LOG"> <parent/> </service>
		<service name="RM"> <parent/> </service>
    
    <any-service> <parent/> </any-service>
	</route>
</start>


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
