<?php

/**
 * @file
 * Hax Gridplate class.
 */

/**
 * The class used for hax_gridplate entities.
 */
class HaxGridplate extends Entity {
  /**
   * Class constructor.
   */
  public function __construct($values = array()) {
    parent::__construct($values, 'hax_gridplate');
  }

  /**
   * Defines the default entity label.
   */
  protected function defaultLabel() {
    return $this->label;
  }

  /**
   * Defines the default entity URI.
   */
  protected function defaultUri() {
    return array('path' => 'hax_gridplate/' . $this->hax_gridplate_id);
  }
}

/**
 * The class used for Hax Gridplate type entities.
 */
class HaxGridplateType extends Entity {
  public $type;
  public $label;

  /**
   * Class constructor.
   */
  public function __construct($values = array()) {
    parent::__construct($values, 'hax_gridplate_type');
  }
}
