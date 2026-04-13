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


<start name="usb_sec_fs" ram="32M" caps="200">
  <binary name="vfs"/>
  <provides>
    <service name="File_system"/>
  </provides>
  <config>
    <vfs>
      <fatfs block="default" writeable="yes"/>
    </vfs>
    <default-policy root="/" writeable="yes"/>
  </config>
  <route>
    <service name="Block"> <child name="usb_sec"/> </service>
    <any-service> <parent/> </any-service>
  </route>
</start>

<!--
<start name="encryptor" ram="32M" caps="200">
  <binary name="encryptor"/>
  
  <provides> <service name="File_system"/> </provides>

  <config>
    <libc stdout="/dev/log" stderr="/dev/log"/>
    <vfs>
      <dir name="dev"> <log/> </dir>
      <dir name="tmp"> <ram/> </dir>
      <dir name="tresor"> <fatfs/> </dir>

      <dir name="snapshot"> <fs/> </dir>
    </vfs>
    <policy label_prefix="snapshot" root="/snapshot" writeable="yes"/>
  </config>
  <route>
    <service name="Block"> <child name="usb_sec"/> </service>
    
    <service name="File_system"><child name="vfs"/></service>
    
    <any-service> <parent/> </any-service>
  </route>
</start>
-->


<start name="se_tresor_init_trust_anchor" ram="4M">
  <config passphrase="foobar" trust_anchor_dir="/usb/trust_anchor">
    <vfs>
      <dir name="usb">
        <fs label="usb_fs -> /"/>
        <dir name="trust_anchor">
          <fs label="ta -> /"/>
        </dir>
      </dir>
    </vfs>
  </config>
  <route>
    <service name="File_system"> <child name="usb_sec_fs"/> </service>
    <any-service> <parent/> </any-service>
  </route>
</start>

<!--
<start name="se_tresor_init" ram="32M" caps="200">  
  <config>
    <vfs>
      <dir name="dev"> <log/> </dir>
      <dir name="tmp"> <ram/> </dir>
      <dir name="usb"> <fs label="usb_fs -> /"/> </dir>
    </vfs>
    <virtual-block-device max_lvl="2" degree="64" num_leaves="512" />
    <free-tree max_lvl="2" degree="64" num_leaves="2048" />
  </config>

  <route>
    <service name="File_system"> <child name="usb_sec_fs"/> </service>
    <any-service> <parent/> </any-service>
  </route>
</start>
-->




<!--
				<start name="tresor_init" ram="4M">
					<config>

						<block-io type="vfs" path="/tresor.img"/>
						<crypto path="/crypto"/>
						<trust-anchor path="/trust_anchor"/>

						<vfs>
							<fs buffer_size="1M"/>
							<tresor_crypto_aes_cbc name="crypto"/>
							<dir name="trust_anchor">
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
-->