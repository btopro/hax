<?php

/**
 * @file
 * Hax Element class.
 */

/**
 * The class used for hax_element entities.
 */
class HaxElement extends Entity {
  /**
   * Class constructor.
   */
  public function __construct($values = array()) {
    parent::__construct($values, 'hax_element');
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
    return array('path' => 'hax_element/' . $this->hax_element_id);
  }
}

/**
 * The class used for Hax Element type entities.
 */
class HaxElementType extends Entity {
  public $type;
  public $label;

  /**
   * Class constructor.
   */
  public function __construct($values = array()) {
    parent::__construct($values, 'hax_element_type');
  }
}
