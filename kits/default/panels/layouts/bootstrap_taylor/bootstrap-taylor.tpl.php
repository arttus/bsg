<?php
/**
 * @file
 * Template for Radix Taylor.
 *
 * Variables:
 * - $css_id: An optional CSS id to use for the layout.
 * - $content: An array of content, each item in the array is keyed to one
 * panel of the layout. This layout supports the following sections:
 */
?>

<div class="panel-display taylor clearfix <?php if (!empty($class)) { print $class; } ?>" <?php if (!empty($css_id)) { print "id=\"$css_id\""; } ?>>

  <div class="container">
    <div class="row">
      <div class="col-md-12 header panel-panel">
        <div class="panel-panel-inner">
          <?php print $content['header']; ?>
        </div>
      </div>
    </div>

    <div class="row">
      <div class="col-md-6 half panel-panel">
        <div class="panel-panel-inner">
          <?php print $content['half']; ?>
        </div>
      </div>
      <div class="col-md-3 quarter1 panel-panel">
        <div class="panel-panel-inner">
          <?php print $content['quarter1']; ?>
        </div>
      </div>
      <div class="col-md-3 quarter2 panel-panel">
        <div class="panel-panel-inner">
          <?php print $content['quarter2']; ?>
        </div>
      </div>
    </div>
    
    <div class="row">
      <div class="col-md-12 footer panel-panel">
        <div class="panel-panel-inner">
          <?php print $content['footer']; ?>
        </div>
      </div>
    </div>
  </div>  

</div><!-- /.taylor -->
