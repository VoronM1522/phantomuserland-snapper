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
    <!--
    <policy label="sequence -> se_tresor_init_trust_anchor -> /" root="/dev/tresor_trust_anchor" writeable="yes"/>
    <policy label="sequence -> se_tresor_init -> ta -> /" root="/usb" writeable="yes"/>
    -->
  </config>
  <route>
    <service name="Block"> <child name="usb_sec"/> </service>
    <any-service> <parent/> </any-service>
  </route>
</start>


<start name="se_vfs" ram="200M" caps="200">
  <binary name="vfs"/>
  <provides><service name="File_system"/></provides>
  <config>
   	<vfs>
   		<dir name="dev">
   			<block name="block" block_buffer_count="128"/>
   		</dir>
      <lwext4 block_device="/dev/block" cache_write_back="yes"
              expand_via_io="no" writeable="yes"
              reporting="no"
              external_cache_size="32M" report_cache="yes"/>
   	</vfs>
   	<policy label="sequence -> se_tresor_init -> tresor -> /" root="/" writeable="yes"/>
  </config>
  <route>
    <service name="Block"> <child name="ahci"/> </service>
    <any-service> <parent/> <any-child/> </any-service>
  </route>
</start>


<start name="sequence" caps="200" ram="128M">
	<config>


    <start name="se_tresor_init_trust_anchor" ram="4M">
      <config passphrase="foobar" trust_anchor_dir="/se_trust_anchor">
        <vfs>
          <dir name="se_trust_anchor">
            <fs/>
          </dir>
        </vfs>
      </config>
      <route>
        <service name="File_system"> <child name="usb_sec_fs"/> </service>
        <any-service> <parent/> </any-service>
      </route>
    </start>


    <start name="se_tresor_init" ram="4M">
      <config>
        <block-io type="vfs" path="/tresor/tresor.img"/> 
        <crypto path="/crypto"/> 
        <trust-anchor path="/trust_anchor"/> 
          <vfs>
          <fs buffer_size="1M"/>
          <tresor_crypto_aes_cbc name="crypto"/>
          <dir name="tresor">
            <fs label="tresor -> /"/>
          </dir>
          <dir name="trust_anchor">
            <fs label="ta -> /"/>
          </dir>
        </vfs>
        <virtual-block-device max_lvl="2" degree="64" num_leaves="512" />
        <free-tree max_lvl="2" degree="64" num_leaves="2048" />
      </config>
      <route>
        <service name="File_system" lable="ta -> /"> <child name="usb_sec_fs"/> </service>
        <service name="File_system" lable="tresor -> /"> <child name="se_vfs"/> </service>
        <any-service> <parent/> </any-service>
      </route>
    </start>


  </config>
  <route>
    <service name="File_system"> <child name="usb_sec_fs"/> </service>
    <service name="File_system"> <child name="se_vfs"/> </service>
    <service name="PD">  <parent/> </service>
    <service name="ROM"> <parent/> </service>
    <service name="LOG"> <parent/> </service>
    <service name="CPU"> <parent/> </service>
    <any-service> <parent/> </any-service>
  </route>
</start>
